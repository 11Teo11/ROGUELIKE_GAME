#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"

class Player;
class Enemy;
class Map;

class Projectile : public Entity
{
private:
    sf::CircleShape shape;
    sf::Vector2f velocity;
    float speed;

public:
    Projectile(sf::Vector2f pos, sf::Vector2f dir);
    Projectile* clone() const;
    void update(float dt, const Map& map) override;
    void draw(sf::RenderWindow& window) override;

    sf::Vector2f getVelocity() const;
    sf::Vector2f getPosition() const;
    bool hitsEnemy(Enemy& enemy);
    bool hitsPlayer(Player& player);
};
