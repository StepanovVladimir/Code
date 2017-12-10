#include "line.h"
#include <iostream>
#include <cmath>

float distanse(sf::Vector2f& mousePosition)
{
    sf::Vector2f vectorDistanse = mousePosition - CENTER;
    return std::sqrt(std::pow(vectorDistanse.x, 2) + std::pow(vectorDistanse.y, 2));
}

void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f& mousePosition)
{
    mousePosition = {float(event.x), float(event.y)};
    std::cout << "distance: " << distanse(mousePosition) << std::endl;
}

void handleEvents(sf::RenderWindow& window, sf::Vector2f& mousePosition)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseMoved:
            onMouseMove(event.mouseMove, mousePosition);
            break;
        default:
            break;
        }
    }
}

void redrawFrame(sf::RenderWindow& window, sf::VertexArray& line, sf::RectangleShape& square)
{
    window.clear(sf::Color(0xFF, 0xFF, 0xFF));
    window.draw(line);
    window.draw(square);
    window.display();
}

int main()
{
    sf::RenderWindow window;
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
        "line", sf::Style::Default, settings);
    sf::VertexArray line(sf::Lines, 2);
    sf::RectangleShape square;
    sf::Vector2f mousePosition = CENTER;
    initializeLine(line, square);
    while (window.isOpen())
    {
        handleEvents(window, mousePosition);
        updateLine(line, mousePosition);
        redrawFrame(window, line, square);
    }
    return 0;
}