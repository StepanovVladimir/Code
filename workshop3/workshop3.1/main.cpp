#include "ball.h"

void handleEvents(sf::RenderWindow& window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
    }
}

void render(sf::RenderWindow& window, Ball& ball)
{
    window.clear(sf::Color(0xFF, 0xFF, 0xFF));
    window.draw(ball.shape);
    window.draw(ball.text);
    window.display();
}

int main()
{
    sf::RenderWindow window;
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    window.create(
        sf::VideoMode(800, 600),
        "Name ball", sf::Style::Default, settings);
    sf::Clock clock;
    Ball ball;
    initializeBall(ball);
    while (window.isOpen())
    {
        handleEvents(window);
        float deltaTime = clock.restart().asSeconds();
        updateBall(ball, deltaTime);
        render(window, ball);
    }
    return 0;
}