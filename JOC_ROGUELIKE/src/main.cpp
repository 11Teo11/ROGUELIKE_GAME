#include <SFML/Graphics.hpp>
#include "Config.h"
#include "Player.h"
#include "Enemy.h"
#include "Map.h"
#include "Game.h"
#include "AssetsLoadException.h"
#include "EntityCreationException.h"
#include "FileLoadException.h"
#include "FontLoadException.h"
#include <iostream>
#include <fstream>

void verifyView(sf::View& view);
void verifyGame(Game& game, sf::RenderWindow& window, sf::View& view, sf::Font& font);
void menu(sf::RenderWindow& window, sf::Font& font);

int main() 
{
    try {
        // ----------------- INIT -----------------
        sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Roguelike Game");
        window.setFramerateLimit(FPS);

        sf::Font font;
        if(!font.loadFromFile(FILE_FONT_GAME_OVER))
            throw FontLoadException("Nu s-a putut incarca fontul");
        
        menu(window, font);

        Map map;
        Player player;
        Game& game = Game::getInstance(map, player);
        
        std::srand(static_cast<unsigned>(std::time(nullptr)));
        
        std::ifstream file(FILE_ENEMIES_POS);
        if (!file.is_open())
        throw FileLoadException("Nu s-a putut deschide fisierul " + FILE_ENEMIES_POS);
        
        int x,y;
        for(int i = 0; i < ENEMIES_TOTAL_NUMBER; i++)
        {
            file >> x >> y;
            x *= TILE_SIZE;
            y *= TILE_SIZE;
            if (x < 0 || y < 0 || x > MAP_WIDTH || y > MAP_HEIGHT)
            throw EntityCreationException("Inamic inafara hartii");
            game.addEntity(new Enemy(sf::Vector2f(x,y)));
        }
        
        sf::View view;
        view.setSize(WINDOW_WIDTH, WINDOW_HEIGHT);
        view.setCenter(player.getPosition());
        
        
        sf::Clock clock;
        // ----------------- INIT -----------------


        while (window.isOpen()) 
        {
            // ----------------- UPDATE -----------------
            float dt = clock.restart().asSeconds();

            sf::Event event;
            while (window.pollEvent(event)) 
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            game.update(dt);

            
            view.setCenter(game.getPlayer().getPosition());
            verifyView(view);
            
            window.setView(view);
            // ----------------- UPDATE -----------------
            
            // ----------------- DRAW -----------------
            window.clear(sf::Color::Black);
            game.draw(window);
            verifyGame(game, window, view, font);

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
            {
                player = Player();
                Game& game = Game::getInstance(map, player);

                std::ifstream file(FILE_ENEMIES_POS);
                if(!file.is_open())
                    throw FileLoadException("Nu s-a putut redeschide fisierul " + FILE_ENEMIES_POS);

                    int x, y;
                    game.clearEntities();
                    for(int i = 0; i < ENEMIES_TOTAL_NUMBER; i++)
                    {
                        file >> x >> y;
                        x *= TILE_SIZE;
                        y *= TILE_SIZE;
                        game.addEntity(new Enemy(sf::Vector2f(x, y)));
                    }
                
                    view.setCenter(player.getPosition());
            }

            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();

            window.display();
            // ----------------- DRAW -----------------
        }

    } 
    catch (const AssetsLoadException& e) 
    {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    } 
    catch (const EntityCreationException& e) 
    {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }
    catch (const FileLoadException& e)
    {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }
    catch (const FontLoadException& e)
    {
        std::cerr << e.what() << '\n';
        return EXIT_FAILURE;
    }

    return 0;
}

void verifyView(sf::View& view)
{
    if (view.getCenter().x < view.getSize().x / 2)
        view.setCenter(view.getSize().x / 2, view.getCenter().y);
    else if (view.getCenter().x > MAP_WIDTH - view.getSize().x / 2)
        view.setCenter(MAP_WIDTH - view.getSize().x / 2, view.getCenter().y);

    if (view.getCenter().y < view.getSize().y / 2)
        view.setCenter(view.getCenter().x, view.getSize().y / 2);
    else if (view.getCenter().y > MAP_HEIGHT - view.getSize().y / 2)
        view.setCenter(view.getCenter().x, MAP_HEIGHT - view.getSize().y / 2);
}

void verifyGame(Game& game, sf::RenderWindow& window, sf::View& view, sf::Font& font)
{
    if(!game.getPlayer().isAlive())
    {
        // ------------------ RED OVERLAY ------------------
        sf::RectangleShape overlay(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
        overlay.setFillColor(GO_OVERLAY_COLOR);
        overlay.setOrigin(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f);
        overlay.setPosition(window.getView().getCenter());
        window.draw(overlay);
        // ------------------ RED OVERLAY ------------------

        // ------------------ GAME OVER TEXT ------------------
        sf::Text goText("GAME OVER", font, GO_TEXT_SIZE);
        goText.setFillColor(GO_TEXT_COLOR);
        goText.setStyle(GO_TEXT_STYLE);

        sf::FloatRect goTextRect = goText.getLocalBounds();
        goText.setOrigin(goTextRect.left + goTextRect.width / 2.f, goTextRect.top + goTextRect.height / 2.f);
        goText.setPosition(view.getCenter().x, view.getCenter().y - GO_TEXT_PADDING);

        window.draw(goText);
        // ------------------ GAME OVER TEXT ------------------

        // ------------------ RESTART TEXT ------------------
        sf::Text restartText("Press R to Restart", font, R_TEXT_SIZE);
        restartText.setFillColor(R_TEXT_COLOR);

        sf::FloatRect restartTextRect = restartText.getLocalBounds();
        restartText.setOrigin(restartTextRect.left + restartTextRect.width / 2.f, restartTextRect.top + restartTextRect.height / 2.f);
        restartText.setPosition(view.getCenter().x, view.getCenter().y + GO_TEXT_SIZE / 2.f + R_TEXT_PADDING);

        window.draw(restartText);
        // ------------------ RESTART TEXT ------------------

        // ------------------ EXIT TEXT ------------------
        sf::Text exitText("Press ESC to Exit", font, E_TEXT_SIZE);
        exitText.setFillColor(E_TEXT_COLOR);

        sf::FloatRect exitTextRect = exitText.getLocalBounds();
        exitText.setOrigin(exitTextRect.left + exitTextRect.width / 2.f, exitTextRect.top + exitTextRect.height / 2.f);
        exitText.setPosition(view.getCenter().x, view.getCenter().y + GO_TEXT_SIZE / 2.f + R_TEXT_SIZE + R_TEXT_PADDING + E_TEXT_PADDING);

        window.draw(exitText);
        // ------------------ EXIT TEXT ------------------
    }
    else
    {
        int cnt_en = 0;
        for(int i = 0;  i < game.getEntities().size(); i++)
        {
            Enemy* enemy = dynamic_cast<Enemy*>(game.getEntities()[i]);
            if(enemy)
                cnt_en ++;
        }
        
        if(cnt_en == 0)
        {
            // ------------------ GREEN OVERLAY ------------------
            sf::RectangleShape overlay(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
            overlay.setFillColor(WG_OVERLAY_COLOR);
            overlay.setOrigin(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f);
            overlay.setPosition(window.getView().getCenter());
            window.draw(overlay);
            // ------------------ GREEN OVERLAY ------------------
        
            // ------------------ WIN GAME TEXT ------------------
            sf::Text wgText("YOU WON", font, WG_TEXT_SIZE);
            wgText.setFillColor(WG_TEXT_COLOR);
            wgText.setStyle(WG_TEXT_STYLE);
        
            sf::FloatRect wgTextRect = wgText.getLocalBounds();
            wgText.setOrigin(wgTextRect.left + wgTextRect.width / 2.f, wgTextRect.top + wgTextRect.height / 2.f);
            wgText.setPosition(view.getCenter().x, view.getCenter().y - WG_TEXT_PADDING);
        
            window.draw(wgText);
            // ------------------ WIN GAME TEXT ------------------

            // ------------------ RESTART TEXT ------------------
            sf::Text restartText("Press R to Restart", font, R_TEXT_SIZE);
            restartText.setFillColor(R_TEXT_COLOR);
    
            sf::FloatRect restartTextRect = restartText.getLocalBounds();
            restartText.setOrigin(restartTextRect.left + restartTextRect.width / 2.f, restartTextRect.top + restartTextRect.height / 2.f);
            restartText.setPosition(view.getCenter().x, view.getCenter().y + GO_TEXT_SIZE / 2.f + R_TEXT_PADDING);
    
            window.draw(restartText);
            // ------------------ RESTART TEXT ------------------
    
            // ------------------ EXIT TEXT ------------------
            sf::Text exitText("Press ESC to Exit", font, E_TEXT_SIZE);
            exitText.setFillColor(E_TEXT_COLOR);
    
            sf::FloatRect exitTextRect = exitText.getLocalBounds();
            exitText.setOrigin(exitTextRect.left + exitTextRect.width / 2.f, exitTextRect.top + exitTextRect.height / 2.f);
            exitText.setPosition(view.getCenter().x, view.getCenter().y + GO_TEXT_SIZE / 2.f + R_TEXT_SIZE + R_TEXT_PADDING + E_TEXT_PADDING);
    
            window.draw(exitText);
            // ------------------ EXIT TEXT ------------------
        }
    }
}

void menu(sf::RenderWindow& window, sf::Font& font)
{
    sf::Text title("Not Another Dungeon", font, M_TEXT_SIZE);
    title.setFillColor(M_TEXT_COLOR);
    sf::FloatRect titleBounds = title.getLocalBounds();
    title.setOrigin(titleBounds.width / 2, titleBounds.height / 2);
    title.setPosition(WINDOW_WIDTH / 2.f, M_TEXT_PADDING);

    sf::Text instructions(
        "To move use W A S D\n"
        "To shoot use Arrow Keys\n"
        "Kill all the enemies to win\n\n"
        "Press Enter to Start",
        font, M_TEXT_INSTRUCTIONS_SIZE
    );

    instructions.setFillColor(M_TEXT_INSTRUCTIONS_COLOR);
    sf::FloatRect instrBounds = instructions.getLocalBounds();
    instructions.setOrigin(instrBounds.width / 2, instrBounds.height / 2);
    instructions.setPosition(WINDOW_WIDTH / 2.f, M_TEXT_INSTRUCTIONS_PADDING);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter)
                return;
        }

        window.clear(sf::Color::Black);
        window.draw(title);
        window.draw(instructions);
        window.display();
    }
}
