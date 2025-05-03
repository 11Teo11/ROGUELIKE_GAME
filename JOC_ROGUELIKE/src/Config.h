#pragma once
#include <SFML/Graphics.hpp>
// Ecran
const unsigned int WINDOW_WIDTH = 1200;
const unsigned int WINDOW_HEIGHT = 900;
const unsigned int FPS = 60;

// Harti
const float TILE_SIZE = 64.f;
const int TILE_ROWS = 80;
const int TILE_COLS = 90;
const int MAP_WIDTH = TILE_SIZE * TILE_COLS;
const int MAP_HEIGHT = TILE_SIZE * TILE_ROWS;

// Dimensiuni player
const float PLAYER_WIDTH = TILE_SIZE * 0.75f;  // 48
const float PLAYER_HEIGHT = TILE_SIZE * 0.75f; // 48
const float PLAYER_SPEED = 200.f;
const float PLAYER_SHOOT_COOLDOWN = 0.2f;
const sf::Vector2f PLAYER_POSITION = sf::Vector2f(4,10);
// const sf::Texture PLAYER_TEXTURES =  // de completat

// Dimensiuni enemy
const float ENEMY_WIDTH = TILE_SIZE * 0.75f;
const float ENEMY_HEIGHT = TILE_SIZE * 0.75f;
const float ENEMY_SPEED = 120.f;
const int ENEMY_MAX_HEALTH = 10;
const float ENEMY_FOLLOW_PLAYER = TILE_SIZE * 2;

// Dimensiuni proiectil
const float PROJECTILE_RADIUS = TILE_SIZE * 0.1f;
const float PROJECTILE_SPEED = 300.f;
const float PROJECTILE_DAMAGE = 3.f;

// Animatie
const float FRAME_DELAY = 0.1f;
