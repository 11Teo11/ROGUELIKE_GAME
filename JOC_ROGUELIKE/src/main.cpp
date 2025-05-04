#include <SFML/Graphics.hpp>
#include "Config.h"
#include "Player.h"
#include "Enemy.h"
#include "Map.h"
#include "Game.h"
#include "AssetsLoadException.h"
#include "EntityCreationException.h"
#include <iostream>

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
        
        sf::Vector2f posEnemies[ENEMIES_NUMBER];
        posEnemies[0] = sf::Vector2f(5, 3) * TILE_SIZE + sf::Vector2f(ENEMY_WIDTH / 2.f, ENEMY_HEIGHT / 2.f);
        posEnemies[1] = sf::Vector2f(7, 9) * TILE_SIZE + sf::Vector2f(ENEMY_WIDTH / 2.f, ENEMY_HEIGHT / 2.f);
        posEnemies[2] = sf::Vector2f(10, 8) * TILE_SIZE + sf::Vector2f(ENEMY_WIDTH / 2.f, ENEMY_HEIGHT / 2.f);

        for(int i = 0; i < ENEMIES_NUMBER; i++)
        {
            if (posEnemies[i].x < 0 || posEnemies[i].y < 0 || posEnemies[i].x > MAP_WIDTH || posEnemies[i].y > MAP_HEIGHT)
                throw EntityCreationException("Inamic inafara hartii");
            game.addEntity(new Enemy(posEnemies[i]));
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

            game.update(dt, player);

            view.setCenter(player.getPosition());
            verifyView(view);

            window.setView(view);
            // ----------------- UPDATE -----------------

            // ----------------- DRAW -----------------
            window.clear(sf::Color::Black);
            game.draw(window, player);
            window.display();
            // ----------------- DRAW -----------------
        }

    } 
    catch (const AssetsLoadException& e) 
    {
        std::cerr << "Eroare la incarcarea hartii: " << e.what() << '\n';
        return EXIT_FAILURE;
    } 
    catch (const EntityCreationException& e) 
    {
        std::cerr << "Eroare entitate: " << e.what() << '\n';
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
