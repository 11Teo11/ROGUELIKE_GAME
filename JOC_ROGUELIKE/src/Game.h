#pragma once
#include <vector>
#include "Entity.h"
#include "Map.h"
#include "Player.h"

class Game {
private:
    Map map;
    Player player;
    std::vector<Entity*> entities;

public:
    Game(Map& map, Player& player);

    void update(float dt);
    void draw(sf::RenderWindow& window);

    void addEntity(Entity* e);
    const std::vector<Entity*>& getEntities() const;
    const Player& getPlayer() const;
};
