#include "ball.h"

void initializeBall(Ball& ball)
{
    ball.shape.setRadius(100);
    ball.shape.setOrigin({100, 100});
    ball.shape.setFillColor(sf::Color(255, 255, 0));
    ball.shape.setPosition({400, 150});
    ball.shape.setOutlineColor(sf::Color(0, 0, 255));
    ball.shape.setOutlineThickness(5);
    ball.font.loadFromFile("arialn.ttf");
    ball.text.setFont(ball.font);
    ball.text.setString("SVP");
    ball.text.setCharacterSize(50);
    ball.text.setFillColor(sf::Color(0, 0, 0));
    ball.text.setPosition({400, 150});
    ball.text.setOrigin({40, 25});
}

void updateBall(Ball& ball, float& deltaTime)
{
    sf::Vector2f position = ball.shape.getPosition();
    ball.speed += ball.speedup * deltaTime;
    position.y += ball.speed * deltaTime;
    if ((position.y + ball.shape.getRadius() + ball.shape.getOutlineThickness() >= 600)
        && (ball.speed > 0))
    {
        ball.speed = -ball.speed;
    }
    ball.shape.setPosition(position);
    ball.text.setPosition(position);
}