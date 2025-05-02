#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <string>

class Map 
{
private:
    std::vector<std::vector<int>> grid;
    sf::RectangleShape tile;
    std::map<std::string, sf::Texture> tileTextures;

    std::string getTileType(int row, int col) const;

public:
    Map();
    void draw(sf::RenderWindow& window);
    bool isWallAt(int x, int y) const;
};