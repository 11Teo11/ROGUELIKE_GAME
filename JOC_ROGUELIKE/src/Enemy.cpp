#include "Config.h"
#include "Enemy.h"
#include "Projectile.h"
#include <cmath>
#include <cstdlib>
#include <ctime>

Enemy::Enemy(sf::Vector2f pos)
{
    shape.setSize(sf::Vector2f(ENEMY_WIDTH,ENEMY_HEIGHT));
    shape.setOrigin(shape.getSize()/2.f);
    shape.setPosition(pos);

    sf::Texture enemyTexture;

    for(int i = 0; i < 4; i++)
    {
        if(enemyTexture.loadFromFile("assets/enemy/enemy" + std::to_string(i) + ".png"))
            textures.push_back(enemyTexture);
    }
    sprite.setTexture(textures[0]);
    sprite.setOrigin(textures[0].getSize().x / 2.f, textures[0].getSize().y / 2.f);
    sprite.setPosition(shape.getPosition());

    speed = ENEMY_SPEED;
    health = ENEMY_MAX_HEALTH;

    animationTimer = 0.f;
    frameDelay = FRAME_DELAY;
    currentFrame = 0;

    direction = sf::Vector2f(0, 1);
    directionTimer = 0.f;
    directionChangeInterval = 1.f;

    healthBarBack.setSize(sf::Vector2f(ENEMY_WIDTH, H_BAR_HEIGHT));
    healthBarBack.setFillColor(H_BAR_BACK_COLOR);
    healthBarBack.setOrigin(ENEMY_WIDTH / 2.f, 0.f);

    healthBarFront.setSize(sf::Vector2f(ENEMY_WIDTH, H_BAR_HEIGHT));
    healthBarFront.setFillColor(H_BAR_FRONT_COLOR_E);
    healthBarFront.setOrigin(ENEMY_WIDTH / 2.f, 0.f);

    shootTimer = 0.f;
    shootCooldown = ENEMY_SHOOT_COOLDOWN;

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
            {
                direction = sf::Vector2f(1, 0);
                sprite.setTexture(textures[0]);
            }
        else if (dir == 1) 
            {
                direction = sf::Vector2f(-1, 0);
                sprite.setTexture(textures[2]);
            }
        else if (dir == 2) 
            {
                direction = sf::Vector2f(0, 1); 
                sprite.setTexture(textures[3]);
            }
        else 
            {
                direction = sf::Vector2f(0, -1); 
                sprite.setTexture(textures[1]);
            }
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

    sprite.setPosition(shape.getPosition());


    sf::Vector2f pos = shape.getPosition();
    healthBarBack.setPosition(pos.x, pos.y - ENEMY_HEIGHT / 2.f - H_BAR_PADDING);
    healthBarFront.setPosition(pos.x, pos.y - ENEMY_HEIGHT / 2.f - H_BAR_PADDING);

    healthBarFront.setSize(sf::Vector2f(ENEMY_WIDTH * health / ENEMY_MAX_HEALTH, H_BAR_HEIGHT));

    if(shootTimer > 0)
        shootTimer -= dt;
}

void Enemy::moveTowardPlayer(const sf::Vector2f& playerPos, const Map& map, float dt)
{
    sf::Vector2f toPlayer = playerPos - shape.getPosition();

    float dist = std::sqrt(toPlayer.x * toPlayer.x + toPlayer.y * toPlayer.y);

    if (dist <= ENEMY_FOLLOW_PLAYER)
    {
        toPlayer = sf::Vector2f(std::abs(toPlayer.x),std::abs(toPlayer.y));
        if (toPlayer.x > toPlayer.y)
            {
                if (shape.getPosition().x > playerPos.x)
                    {
                        direction = sf::Vector2f(-1,0);
                        sprite.setTexture(textures[2]);
                    }
                else
                    {
                        direction = sf::Vector2f(1,0);
                        sprite.setTexture(textures[0]);
                    }
            }
        else
            {
                if(shape.getPosition().y > playerPos.y)
                    {
                        direction = sf::Vector2f(0,-1);
                        sprite.setTexture(textures[1]);
                    }
                else
                    {
                        direction = sf::Vector2f(0,1);
                        sprite.setTexture(textures[3]);
                    }
            }
        directionTimer = 0.f;
    }

    update(dt, map);
}

void Enemy::draw(sf::RenderWindow& window)
{
    window.draw(sprite);
    window.draw(healthBarBack);
    window.draw(healthBarFront);
}

sf::Vector2f Enemy::getPosition() const
{
    return shape.getPosition();
}

const std::vector<Projectile>& Enemy::getProjectiles() const {
    return projectiles;
}

void Enemy::takeDamage(int dmg)
{
    health -= dmg;
}

bool Enemy::isAlive() const 
{
    return health > 0;
}

void Enemy::shootPlayer(const sf::Vector2f& playerPos)
{
    if (shootTimer > 0.f)
        return;
    
    sf::Vector2f toPlayer = playerPos - shape.getPosition();

    float dist = std::sqrt(toPlayer.x * toPlayer.x + toPlayer.y * toPlayer.y);

    if (dist < ENEMY_FOLLOW_PLAYER)
    {
        sf::Vector2f dir = toPlayer / dist; // directie normalizata
        projectiles.emplace_back(shape.getPosition(), dir);
        shootTimer = shootCooldown;
    }
}

void Enemy::updateProjectiles(float dt, const Map& map, Player& player)
{
    if ( shootTimer > 0.f)
        shootTimer -= dt;
    
    for(int i = 0; i < projectiles.size(); i++)
    {
        projectiles[i].update(dt, map);

        if(projectiles[i].hitsPlayer(player))
        {
            player.takeDamage(PROJECTILE_DAMAGE);
            projectiles.erase(projectiles.begin() + i);
            i--;
            break;
        }

        if (i >= 0 && projectiles[i].getVelocity() == sf::Vector2f(0.f,0.f))
        {
            projectiles.erase(projectiles.begin() + i);
            i--;
        }
    }
}

void Enemy::drawProjectiles(sf::RenderWindow& window)
{
    for ( int i = 0; i < projectiles.size(); i++)
        projectiles[i].draw(window);
}
