#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

// Fisiere
const std::string FILE_ENEMIES_POS = "src/enemies.txt";
const std::string FILE_FONT_GAME_OVER = "assets/fonts/DSketch.otf";

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

// Dimensiuni enemy
const float ENEMY_WIDTH = TILE_SIZE * 0.75f;
const float ENEMY_HEIGHT = TILE_SIZE * 0.75f;
const float ENEMY_SPEED = 120.f;
const int ENEMY_MAX_HEALTH = 10;
const float ENEMY_FOLLOW_PLAYER = TILE_SIZE * 2;
const int ENEMIES_TOTAL_NUMBER = 20;
const float ENEMY_SHOOT_COOLDOWN = 0.8f;
const float ENEMY_SHOOT_PLAYER = TILE_SIZE * 4;

// Dimensiuni proiectil
const float PROJECTILE_RADIUS = TILE_SIZE * 0.1f;
const float PROJECTILE_SPEED = 350.f;
const int PROJECTILE_DAMAGE = 3;
const float PROJECTILE_HIT_RADIUS = 20.f;

// Animatie
const float FRAME_DELAY = 0.1f;

// Bara viata
const float H_BAR_HEIGHT = 5.f;
const sf::Color H_BAR_BACK_COLOR = sf::Color(50,50,50);
const sf::Color H_BAR_FRONT_COLOR_E = sf::Color::Red;
const sf::Color H_BAR_FRONT_COLOR_P = sf::Color::Green;
const float H_BAR_PADDING = 20.f;
const float H_CRTITICAL_TRESHOLD = 0.20f;

// Ecran meniu
const float M_TEXT_SIZE = 100.f;
const sf::Color M_TEXT_COLOR = sf::Color::White;
const float M_TEXT_PADDING = 200.f;
const float M_TEXT_INSTRUCTIONS_SIZE = 60.f;
const sf::Color M_TEXT_INSTRUCTIONS_COLOR = sf::Color::White;
const float M_TEXT_INSTRUCTIONS_PADDING = 500.f;

// Ecran Game Over
const sf::Color GO_OVERLAY_COLOR = sf::Color(255, 0, 0, 100);
const float GO_TEXT_SIZE = 120.f;
const sf::Color GO_TEXT_COLOR = sf::Color::White;
const sf::Text::Style GO_TEXT_STYLE = sf::Text::Bold;
const float GO_TEXT_PADDING = 60.f;

// Ecran Win Game
const sf::Color WG_OVERLAY_COLOR = sf::Color(0, 255, 0, 100);
const float WG_TEXT_SIZE = 120.f;
const sf::Color WG_TEXT_COLOR = sf::Color::White;
const sf::Text::Style WG_TEXT_STYLE = sf::Text::Bold;
const float WG_TEXT_PADDING = 60.f;

// Text Restart
const float R_TEXT_SIZE = 60.f;
const sf::Color R_TEXT_COLOR = sf::Color::White;
const float R_TEXT_PADDING = 20.f;

// Text Exit
const float E_TEXT_SIZE = 60.f;
const sf::Color E_TEXT_COLOR = sf::Color::White;
const float E_TEXT_PADDING = 20.f;
