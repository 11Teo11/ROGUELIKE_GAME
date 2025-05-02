#pragma once
#include <SFML/Graphics.hpp>

class Entity // clasa abstracta
{
protected:
    static int instanceCount;
public:
    virtual Entity* clone() const = 0;
    virtual void update(float dt, const class Map& map) = 0; // functii virtuale pure
    virtual void draw(sf::RenderWindow& window) = 0;
    virtual sf::Vector2f getPosition() const = 0;
    static int getInstanceCount() { return instanceCount = 0; } // metoda statica pentru a obtine numarul de instante

    virtual ~Entity() {}
};