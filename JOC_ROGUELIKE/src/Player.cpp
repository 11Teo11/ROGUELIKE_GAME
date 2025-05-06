#include "Config.h"
#include "Player.h"
#include <SFML/Window/Keyboard.hpp>

Player::Player() 
{
    shape.setSize(sf::Vector2f(PLAYER_WIDTH, PLAYER_HEIGHT));
    shape.setOrigin(shape.getSize()/2.f);
    shape.setPosition(PLAYER_POSITION.x * TILE_SIZE, PLAYER_POSITION.y * TILE_SIZE);

    sf::Texture playerTexture;

    for(int i = 1; i <= 12; i++)
    {
        if(playerTexture.loadFromFile("assets/player/player_" + std::to_string(i) + ".png"))
            textures.push_back(playerTexture); 
    }
    sprite.setTexture(textures[7]);
    sprite.setScale(2.5f, 2.5f);
    sprite.setOrigin(textures[7].getSize().x / 2.f, textures[7].getSize().y / 2.f);
    sprite.setPosition(shape.getPosition());
    
    speed = PLAYER_SPEED;
    health = PLAYER_MAX_HEALTH;
    currentDirection = sf::Vector2f(0, 1);
    shootCooldown = PLAYER_SHOOT_COOLDOWN;
    shootTimer = 0.f;
    animationTimer = 0.f;
    frameDelay = FRAME_DELAY;
    currentFrame = 7;

    healthBarBack.setSize(sf::Vector2f(PLAYER_WIDTH, H_BAR_HEIGHT));
    healthBarBack.setFillColor(H_BAR_BACK_COLOR);
    healthBarBack.setOrigin(PLAYER_WIDTH / 2.f, 0.f);

    healthBarFront.setSize(sf::Vector2f(ENEMY_WIDTH, H_BAR_HEIGHT));
    healthBarFront.setFillColor(H_BAR_FRONT_COLOR_P);
    healthBarFront.setOrigin(PLAYER_WIDTH / 2.f, 0.f);
}

Player* Player::clone() const 
{
    return new Player(*this);
}

void Player::update(float dt, const Map& map) 
{
    sf::Vector2f direction(0,0);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        direction = sf::Vector2f(0, -1);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        direction = sf::Vector2f(0, 1);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        direction = sf::Vector2f(-1, 0);
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        direction = sf::Vector2f(1, 0);

    int base = 0;
    if (currentDirection == sf::Vector2f(0,-1))
        base = 0;
    else if (currentDirection ==  sf::Vector2f(1,0))
        base = 3;
    else if (currentDirection ==  sf::Vector2f(0,1))
        base = 6;
    else if (currentDirection ==  sf::Vector2f(-1,0))
        base = 9;


    if (direction != sf::Vector2f(0,0))
        {
            this->currentDirection = direction;
            animationTimer += dt;

            if( animationTimer >= frameDelay)
            {
                animationTimer = 0.f;

                if(currentFrame == base)
                    currentFrame = base + 2;
                else
                    currentFrame = base;
            }
        }
    else
        currentFrame = base + 1;
    
    sprite.setTexture(textures[currentFrame]);

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

    sprite.setPosition(shape.getPosition());

    sf::Vector2f pos = shape.getPosition();
    healthBarBack.setPosition(pos.x, pos.y - PLAYER_HEIGHT / 2.f - H_BAR_PADDING);
    healthBarFront.setPosition(pos.x, pos.y - PLAYER_HEIGHT / 2.f - H_BAR_PADDING);

    healthBarFront.setSize(sf::Vector2f(PLAYER_WIDTH * health / PLAYER_MAX_HEALTH, H_BAR_HEIGHT));
}



void Player::handleShooting()
{
    sf::Vector2f shootDir(0,0);

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        shootDir = sf::Vector2f(0,-1);
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        shootDir = sf::Vector2f(0,1);
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        shootDir = sf::Vector2f(1,0);
    else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        shootDir = sf::Vector2f(-1,0);

    if( shootDir != sf::Vector2f(0,0) && shootTimer <= 0)
    {
        projectiles.emplace_back(shape.getPosition(), shootDir);
        shootTimer = shootCooldown;
    }
}

void Player::updateProjectiles(float dt, const Map& map, std::vector<Entity*>& entities)
{
    if ( shootTimer > 0.f)
        shootTimer -= dt;
    
    for(int i = 0; i < projectiles.size(); i++)
    {
        projectiles[i].update(dt, map);

        for (int j = 0; j < entities.size(); j++) 
        {
            Enemy* enemy = dynamic_cast<Enemy*>(entities[j]);
            if (enemy && projectiles[i].hitsEnemy(*enemy)) 
            {
                enemy->takeDamage(PROJECTILE_DAMAGE);
                projectiles.erase(projectiles.begin() + i);
                i--;
                break;
            }
        }

        if (i >= 0 && projectiles[i].getVelocity() == sf::Vector2f(0.f,0.f))
        {
            projectiles.erase(projectiles.begin() + i);
            i--;
        }
    }
}
    
void Player::draw(sf::RenderWindow& window) 
{
    window.draw(sprite);
    window.draw(healthBarBack);
    window.draw(healthBarFront);
}
    
void Player::drawProjectiles(sf::RenderWindow& window)
{
    for ( int i = 0; i< projectiles.size(); i++)
        projectiles[i].draw(window);
}
    
sf::Vector2f Player::getPosition() const 
{
    return shape.getPosition();
}
    
const std::vector<Projectile>& Player::getProjectiles() const
{
    return projectiles;
}
