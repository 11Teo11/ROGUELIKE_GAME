#include "Config.h"
#include "Projectile.h"
#include "Map.h"
#include "Enemy.h"
#include <cmath>

Projectile::Projectile(sf::Vector2f pos, sf::Vector2f dir)
{
    shape.setRadius(PROJECTILE_RADIUS);
    shape.setFillColor(sf::Color::Red);
    shape.setOrigin(PROJECTILE_RADIUS, PROJECTILE_RADIUS);
    shape.setPosition(pos);

    this->speed = PROJECTILE_SPEED;
    this->velocity = dir * PROJECTILE_SPEED;
}

Projectile* Projectile::clone() const 
{
    return new Projectile(*this);
}

void Projectile::update(float dt, const Map& map)
{
    sf::Vector2f nextPos = shape.getPosition() + velocity * dt;
    float radius = shape.getRadius();
    
    if (map.isWallAt(nextPos.x - radius, nextPos.y - radius) ||
        map.isWallAt(nextPos.x + radius, nextPos.y - radius) ||
        map.isWallAt(nextPos.x - radius, nextPos.y + radius) ||
        map.isWallAt(nextPos.x + radius, nextPos.y + radius)) 
        {
        velocity = sf::Vector2f(0.f, 0.f);
        }

    shape.move(velocity * dt);
}

void Projectile::draw(sf::RenderWindow& window) 
{
    window.draw(shape);
}

sf::Vector2f Projectile::getVelocity() const
{
    return this->velocity;
}

sf::Vector2f Projectile::getPosition() const 
{
    return shape.getPosition();
}

bool Projectile::hitsEnemy(Enemy& enemy)
{
    float dx = shape.getPosition().x - enemy.getPosition().x;
    float dy = shape.getPosition().y - enemy.getPosition().y;
    float distance = std::sqrt(dx * dx + dy * dy);

    if (distance < shape.getRadius() + 20.f) { // ajustăm raza de coliziune
        return true;
    }
    return false;
    // return distance < shape.getRadius() + 20.f;
}