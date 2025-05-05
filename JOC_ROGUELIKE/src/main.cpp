#include <SFML/Graphics.hpp>
#include "Config.h"
#include "Player.h"
#include "Enemy.h"
#include "Map.h"
#include "Game.h"
#include "AssetsLoadException.h"
#include "EntityCreationException.h"
#include "FileLoadException.h"
#include <iostream>
#include <fstream>

void verifyView(sf::View& view);

int main() 
{
    try {
        // ----------------- INIT -----------------
        sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Roguelike Game");
        window.setFramerateLimit(FPS);

        Map map;
        Player player;
        Game game(map, player);

        std::srand(static_cast<unsigned>(std::time(nullptr)));

        std::ifstream file(FILE_ENEMIES_POS);
        if (!file.is_open())
            throw FileLoadException("Nu s-a putut deschide fisierul " + FILE_ENEMIES_POS);

        int x,y;
        for(int i = 0; i < ENEMIES_NUMBER; i++)
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
