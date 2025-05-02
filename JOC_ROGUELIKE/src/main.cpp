#include <SFML/Graphics.hpp>
#include "Config.h"
#include "Player.h"
#include "Enemy.h"
#include "Map.h"
#include "AssetsLoadException.h"
#include "EntityCreationException.h"
#include <vector>
#include <iostream>

int main() 
{
    try
    {
        // ----------------- INIT -----------------
        sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Roguelike Game");
        window.setFramerateLimit(FPS);
    
        Player player(PLAYER_POSITION);
        Map map;
        
        std::vector<Entity*> entities;
        
        sf::Vector2f pos1 = sf::Vector2f(5,3)*TILE_SIZE + sf::Vector2f(ENEMY_WIDTH/2.f, ENEMY_HEIGHT/2.f);
        if (pos1.x < 0 || pos1.y < 0 || pos1.x > MAP_WIDTH || pos1.y > MAP_HEIGHT)
        {
            throw EntityCreationException("Inamic inafara hartii");
        }
        entities.push_back(new Enemy(pos1));
        
        sf::Vector2f pos2 = sf::Vector2f(7,9)*TILE_SIZE + sf::Vector2f(ENEMY_WIDTH/2.f, ENEMY_HEIGHT/2.f);
        if (pos2.x < 0 || pos2.y < 0 || pos2.x > MAP_WIDTH || pos2.y > MAP_HEIGHT)
        {
            throw EntityCreationException("Enemy");
        }
        entities.push_back(new Enemy(pos2));
        
        sf::Vector2f pos3 = sf::Vector2f(10,8)*TILE_SIZE + sf::Vector2f(ENEMY_WIDTH/2.f, ENEMY_HEIGHT/2.f);
        if (pos3.x < 0 || pos3.y < 0 || pos3.x > MAP_WIDTH || pos3.y > MAP_HEIGHT)
        {
            throw EntityCreationException("Enemy");
        }
        entities.push_back(new Enemy(pos3));
        
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
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                window.close();
            }
            
            player.update(dt, map);
            player.handleShooting();
            player.updateProjectiles(dt, map, entities);
            
            for (int i = 0; i < entities.size(); i++)
            {
                Enemy* enemy = dynamic_cast<Enemy*>(entities[i]);
                if (enemy)
                {
                    enemy->moveTowardPlayer(player.getPosition(), map, dt);
                }
            }
            
            for(int i = 0; i < entities.size(); i++)
            {
                Enemy* enemy = dynamic_cast<Enemy*>(entities[i]);
                if( enemy && !enemy->isAlive())
                {
                    entities.erase(entities.begin() + i);
                    i --;
                }
            }
            
            view.setCenter(player.getPosition());
            if (view.getCenter().x < view.getSize().x/2)
            view.setCenter(view.getSize().x/2, view.getCenter().y);
            else if (view.getCenter().x > MAP_WIDTH - view.getSize().x/2)
            view.setCenter(MAP_WIDTH - view.getSize().x/2, view.getCenter().y);
            
            if (view.getCenter().y < view.getSize().y/2)
            view.setCenter(view.getCenter().x, view.getSize().y/2);
            else if ( view.getCenter().y > MAP_HEIGHT - view.getSize().y/2 )
            view.setCenter(view.getCenter().x, MAP_HEIGHT - view.getSize().y/2);
            
            window.setView(view);
            // ----------------- UPDATE -----------------
            
            // ----------------- DRAW -----------------
            window.clear(sf::Color::Black);
            map.draw(window);
            player.drawProjectiles(window);
            
            for (int i = 0; i < entities.size(); i++)
            {
                Enemy* enemy = dynamic_cast<Enemy*>(entities[i]);
                if (enemy)
                enemy->draw(window);
            }
            
            player.draw(window);
            
            window.display();
            // ----------------- DRAW -----------------
        }
        
        for (Entity* entity : entities)
        {
            if( entity != &player)
            delete entity;
        }
    }
    catch(const AssetsLoadException& e)
    {
        std::cerr << "Eroare la incarcarea hartii: " << e.what() << '\n';
        return EXIT_FAILURE;
    }
    catch(const EntityCreationException& e)
    {
        std::cerr << "Eroare entitate: "<< e.what() << '\n';
        return EXIT_FAILURE;
    }

    return 0;
}