#include "ball.h"

void initializeBall(sf::CircleShape& shape)
{
    shape.setRadius(100);
    shape.setOrigin({100, 100});
    shape.setFillColor(sf::Color(255, 255, 0));
    shape.setPosition({400, 300});
    shape.setOutlineColor(sf::Color(0, 0, 255));
    shape.setOutlineThickness(5);
}