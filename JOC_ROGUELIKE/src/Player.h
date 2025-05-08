#pragma once
#include "Entity.h"
#include "Map.h"
#include "Enemy.h"
#include "Projectile.h"
#include <SFML/Graphics.hpp>
#include <vector>

class Player : public Entity 
{
private:
    sf::RectangleShape shape;
    std::vector<sf::Texture> textures;
    sf::Sprite sprite;
    float speed;
    sf::Vector2f currentDirection;
    std::vector<Projectile> projectiles;
    float shootTimer;
    float shootCooldown;
    float animationTimer;
    float frameDelay;
    int currentFrame;
    int health;
    sf::RectangleShape healthBarBack;
    sf::RectangleShape healthBarFront;

    void setTextures(); 

public:
    Player();
    Player* clone() const ;

    void update(float dt,const Map& map) override; 
    void updateProjectiles(float dt, const Map& map, std::vector<Entity*>& entities);

    void draw(sf::RenderWindow& window) override;
    void drawProjectiles(sf::RenderWindow& window);

    sf::Vector2f getPosition() const override;

    void handleShooting();
    const std::vector<Projectile>& getProjectiles() const;
    void takeDamage(int dmg);
};
