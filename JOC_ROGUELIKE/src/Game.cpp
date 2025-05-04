#include "Game.h"
#include "Enemy.h"
#include "Player.h"
#include <iostream>

Game::Game(Map& map, Player& player)
{
    this->map = map;
    this->player = player;
}

void Game::addEntity(Entity* e) 
{
    entities.push_back(e);
}

const std::vector<Entity*>& Game::getEntities() const 
{
    return entities;
}

void Game::update(float dt, Player& player) 
{
    player.update(dt, map);
    player.handleShooting();
    player.updateProjectiles(dt, map, entities);

    for(int i = 0; i < entities.size(); i++)
    {
        Enemy* enemy = dynamic_cast<Enemy*>(entities[i]);
        if (enemy)
        {
            if(enemy->isAlive())
                enemy->moveTowardPlayer(player.getPosition(), map, dt);
            else
            {
                delete(enemy);
                entities.erase(entities.begin() + i);
                i--;
            }
        }
    }
}

void Game::draw(sf::RenderWindow& window, Player& player) 
{
    map.draw(window);
    player.drawProjectiles(window);
    for(int i = 0; i < entities.size(); i++)
    {
        entities[i]->draw(window);
    }
    player.draw(window);
}
