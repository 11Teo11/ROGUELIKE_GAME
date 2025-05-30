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

    Game(const Map& map, const Player& player);

    Game(const Game&) = delete;
    Game& operator=(const Game&) =  delete;
public:
    static Game& getInstance(const Map& m, const Player& p){
        static Game instance(m, p);
        return instance;
    }

    void update(float dt);

    void draw(sf::RenderWindow& window);

    void addEntity(Entity* e);

    const std::vector<Entity*>& getEntities() const;
    const Player& getPlayer() const;

    void clearEntities();
};
