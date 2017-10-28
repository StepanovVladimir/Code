#include <SFML/Graphics.hpp>
#include <cmath>
#include <algorithm>

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
    arrow.setFillColor(sf::Color(0xFF, 0xFF, 0));
    arrow.setOutlineColor(sf::Color(0, 0, 0));
    arrow.setOutlineThickness(3);
}

float toDegrees(float radians)
{
    return float(double(radians) * 180.0 / M_PI);
}

void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition)
{
    mousePosition = {float(event.x), float(event.y)};
}

void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition)
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

void update(const sf::Vector2f &mousePosition, sf::ConvexShape &arrow, float &dt)
{
    const sf::Vector2f delta = mousePosition - arrow.getPosition();
    float angle = atan2(delta.y, delta.x);
    if (angle < 0)
    {
        angle = angle + 2 * M_PI;
    }
    angle = toDegrees(angle);
    const float timeRotation = 90 * dt;
    const float mouseRotation = std::abs(angle - arrow.getRotation());
    if (angle > arrow.getRotation())
    {
        if ((angle - 180) < arrow.getRotation())
        {
            arrow.setRotation(arrow.getRotation() + std::min(timeRotation, mouseRotation));
        }
        else
        {
            arrow.setRotation(arrow.getRotation() - std::min(timeRotation, mouseRotation));
        }
    }
    else
    {
        if ((angle + 180) > arrow.getRotation())
        {
            arrow.setRotation(arrow.getRotation() - std::min(timeRotation, mouseRotation));
        }
        else
        {
            arrow.setRotation(arrow.getRotation() + std::min(timeRotation, mouseRotation));
        }
    }

    if ((delta.x != 0) && (delta.y != 0))
    {
        sf::Vector2f direction = {
            delta.x / std::sqrt(delta.x * delta.x + delta.y * delta.y),
            delta.y / std::sqrt(delta.x * delta.x + delta.y * delta.y)};
        sf::Vector2f timePosition = direction * 20.f * dt;
        arrow.setPosition(arrow.getPosition() + timePosition);
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
    sf::Clock clock;

    sf::ConvexShape arrow;
    sf::Vector2f mousePosition;

    initArrow(arrow);
    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        float dt = clock.restart().asSeconds();
        update(mousePosition, arrow, dt);
        redrawFrame(window, arrow);
    }
}
