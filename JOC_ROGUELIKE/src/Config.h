#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

// Fisiere
const std::string FILE_ENEMIES_POS = "src/enemies.txt";

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
const float PLAYER_WIDTH = TILE_SIZE * 0.75f;
const float PLAYER_HEIGHT = TILE_SIZE * 0.75f;
const float PLAYER_SPEED = 200.f;
const int PLAYER_MAX_HEALTH = 50;
const float PLAYER_SHOOT_COOLDOWN = 0.2f;
const sf::Vector2f PLAYER_POSITION = sf::Vector2f(4,10);
// const sf::Texture PLAYER_TEXTURES =  // de completat

// Dimensiuni enemy
const float ENEMY_WIDTH = TILE_SIZE * 0.75f;
const float ENEMY_HEIGHT = TILE_SIZE * 0.75f;
const float ENEMY_SPEED = 120.f;
const int ENEMY_MAX_HEALTH = 10;
const float ENEMY_FOLLOW_PLAYER = TILE_SIZE * 2;
const int ENEMIES_TOTAL_NUMBER = 20;

// Dimensiuni proiectil
const float PROJECTILE_RADIUS = TILE_SIZE * 0.1f;
const float PROJECTILE_SPEED = 300.f;
const int PROJECTILE_DAMAGE = 3;

// Animatie
const float FRAME_DELAY = 0.1f;

// Bara viata
const float H_BAR_HEIGHT = 5.f;
const sf::Color H_BAR_BACK_COLOR = sf::Color(50,50,50);
const sf::Color H_BAR_FRONT_COLOR_E = sf::Color::Red;
const sf::Color H_BAR_FRONT_COLOR_P = sf::Color::Green;
const float H_BAR_PADDING = 20.f;
