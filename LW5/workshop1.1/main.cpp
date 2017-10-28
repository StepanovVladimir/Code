#include <SFML/Graphics.hpp>
#include <cmath>

void initArrow(sf::ConvexShape &arrow)
{
    arrow.setPosition({400, 300});
    arrow.setPointCount(7);
    arrow.setPoint(0, {80, 0});
    arrow.setPoint(1, {0, -80});
    arrow.setPoint(2, {0, -40});
    arrow.setPoint(3, {-80, -40});
    arrow.setPoint(4, {-80, 40});
    arrow.setPoint(5, {0, 40});
    arrow.setPoint(6, {0, 80});
    arrow.setRotation(-80);
    arrow.setFillColor(sf::Color(0xFF, 0xFF, 0));
    arrow.setOutlineColor(sf::Color(0, 0, 0));
    arrow.setOutlineThickness(3);
}

void pollEvents(sf::RenderWindow &window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        default:
            break;
        }
    }
}

void redrawFrame(sf::RenderWindow &window, sf::ConvexShape &arrow)
{
    window.clear(sf::Color(0xFF, 0xFF, 0xFF));
    window.draw(arrow);
    window.display();
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Arrow", sf::Style::Default, settings);

    sf::ConvexShape arrow;

    initArrow(arrow);
    while (window.isOpen())
    {
        pollEvents(window);
        redrawFrame(window, arrow);
    }
}