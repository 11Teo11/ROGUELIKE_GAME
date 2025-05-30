#include "Game.h"
#include "Enemy.h"
#include "Player.h"
#include <iostream>

Game::Game(const Map& map,const Player& player) : map(map), player(player) {}

void Game::addEntity(Entity* e) 
{
    entities.push_back(e);
}

const std::vector<Entity*>& Game::getEntities() const 
{
    return entities;
}

const Player& Game::getPlayer() const
{
    return player;
}

void Game::update(float dt) 
{
    if(player.isAlive())
    {
        player.update(dt, map);
        player.handleShooting();
        player.updateProjectiles(dt, map, entities);
    }

    for(int i = 0; i < entities.size(); i++)
    {
        Enemy* enemy = dynamic_cast<Enemy*>(entities[i]);
        if (enemy)
        {
            if(enemy->isAlive())
                {
                    enemy->moveTowardPlayer(player.getPosition(), map, dt);
                    enemy->shootPlayer(player.getPosition());
                    enemy->updateProjectiles(dt, map, player);
                }
            else
            {
                delete(enemy);
                entities.erase(entities.begin() + i);
                i--;
            }
        }
    }
}

void Game::draw(sf::RenderWindow& window) 
{
    map.draw(window);
    
    player.drawProjectiles(window);

    for(int i = 0; i < entities.size(); i++)
    {
        Enemy* enemy = dynamic_cast<Enemy*>(entities[i]);
        if(enemy)
            enemy->drawProjectiles(window);

        entities[i]->draw(window);
    }
    player.draw(window);
}

void Game::clearEntities()
{
    for(int i = 0; i < entities.size(); i++)
        {
            Player* player = dynamic_cast<Player*>(entities[i]);
            if(!player)
                delete entities[i];
        }
}
