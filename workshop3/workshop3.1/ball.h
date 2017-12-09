#pragma once

#include <SFML/Graphics.hpp>

struct Ball
{
    sf::CircleShape shape;
    sf::Font font;
    sf::Text text;
    float speed = 0;
    float speedup = 1000;
};

void initializeBall(Ball& ball);
void updateBall(Ball& ball, float& deltaTime);