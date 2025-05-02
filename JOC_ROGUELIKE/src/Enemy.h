#pragma once
#include "Entity.h"
#include "Map.h"
#include <SFML/Graphics.hpp>
#include <vector>

class Enemy : public Entity
{
private:
    sf::RectangleShape shape;
    std::vector<sf::Texture> textures;
    sf::Sprite sprite;
    float speed;
    sf::Vector2f direction;
    float directionTimer;
    float directionChangeInterval;
    float animationTimer;
    float frameDelay;
    int currentFrame;
    int health;
    
public:
    Enemy(sf::Vector2f pos);
    Enemy* clone() const override;
    void update(float dt,const Map& map) override; 

    void draw(sf::RenderWindow& window) override;

    sf::Vector2f getPosition() const override;

    void takeDamage(int dmg);
    bool isAlive() const;

    void moveTowardPlayer(const sf::Vector2f& playerPos, const Map& map, float dt);
    void randomMovement(float dt, const Map& map);
};