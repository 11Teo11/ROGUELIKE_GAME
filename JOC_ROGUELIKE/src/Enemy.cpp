#include "Config.h"
#include "Enemy.h"
#include <cmath>
#include <cstdlib>
#include <ctime>

Enemy::Enemy(sf::Vector2f pos)
{
    shape.setSize(sf::Vector2f(ENEMY_WIDTH,ENEMY_HEIGHT));
    shape.setOrigin(shape.getSize()/2.f);
    shape.setPosition(pos);

    shape.setFillColor(sf::Color::Red);
    shape.setOutlineThickness(2.f);
    shape.setOutlineColor(sf::Color::Black);

    speed = ENEMY_SPEED;
    health = ENEMY_MAX_HEALTH;

    animationTimer = 0.f;
    frameDelay = FRAME_DELAY;
    currentFrame = 0;

    direction = sf::Vector2f(0, 1);
    directionTimer = 0.f;
    directionChangeInterval = 1.f;

    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

Enemy* Enemy::clone() const 
{
    return new Enemy(*this);
}

void Enemy::update(float dt, const Map& map)
{
    directionTimer += dt;

    if (directionTimer >= directionChangeInterval)
    {
        directionTimer = 0.f;

        int dir = std::rand() % 4;
        if (dir == 0) 
            direction = sf::Vector2f(1, 0);
        else if (dir == 1) 
            direction = sf::Vector2f(-1, 0);
        else if (dir == 2) 
            direction = sf::Vector2f(0, 1); 
        else 
            direction = sf::Vector2f(0, -1); 
    }

    sf::Vector2f movement = direction * speed * dt;
    sf::Vector2f nextPos = shape.getPosition() + movement;
    float halfW = shape.getSize().x / 2.f;
    float halfH = shape.getSize().y / 2.f;

    bool collision = false;
    if (direction.y < 0)
        collision = map.isWallAt(nextPos.x - halfW, nextPos.y - halfH) ||
                    map.isWallAt(nextPos.x + halfW, nextPos.y - halfH);
    else if (direction.y > 0)
        collision = map.isWallAt(nextPos.x - halfW, nextPos.y + halfH) ||
                    map.isWallAt(nextPos.x + halfW, nextPos.y + halfH);
    else if (direction.x < 0)
        collision = map.isWallAt(nextPos.x - halfW, nextPos.y - halfH) ||
                    map.isWallAt(nextPos.x - halfW, nextPos.y + halfH);
    else if (direction.x > 0)
        collision = map.isWallAt(nextPos.x + halfW, nextPos.y - halfH) ||
                    map.isWallAt(nextPos.x + halfW, nextPos.y + halfH);

    if (!collision)
        shape.move(movement);
}

void Enemy::moveTowardPlayer(const sf::Vector2f& playerPos, const Map& map, float dt)
{
    sf::Vector2f toPlayer = playerPos - shape.getPosition();

    float dist = std::sqrt(toPlayer.x * toPlayer.x + toPlayer.y * toPlayer.y);

    if (dist <= 120.f) // config
    {
        toPlayer = sf::Vector2f(std::abs(toPlayer.x),std::abs(toPlayer.y));
        if (toPlayer.x > toPlayer.y)
            {
                if (shape.getPosition().x > playerPos.x)
                    direction = sf::Vector2f(-1,0);
                else
                    direction = sf::Vector2f(1,0);
            }
        else
            {
                if(shape.getPosition().y > playerPos.y)
                    direction = sf::Vector2f(0,-1);
                else
                    direction = sf::Vector2f(0,1);
            }
        directionTimer = 0.f;
    }

    update(dt, map); // Folosește direcția actualizată
}

void Enemy::draw(sf::RenderWindow& window)
{
    window.draw(shape);
}

sf::Vector2f Enemy::getPosition() const
{
    return shape.getPosition();
}

void Enemy::takeDamage(int dmg)
{
    health -= dmg;
}

bool Enemy::isAlive() const 
{
    return health > 0;
}