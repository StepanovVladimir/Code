#include <SFML/Graphics.hpp>
#include <cmath>
#include <algorithm>

void initArrow(sf::ConvexShape &arrow)
{
    // Инициализирует стрелку
}

float toDegrees(float radians)
{
    // Переводит радианы в градусы
}

void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition)
{
    // Обрабатывает событие MouseMove, обновляя позицию мыши
}

void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition)
{
    // Опрашивает и обрабатывает доступные события в цикле
}

void update(const sf::Vector2f &mousePosition, sf::ConvexShape &arrow, float &dt)
{
    // Обновляет фигуру, двигающуюся за мышью
}

void redrawFrame(sf::RenderWindow &window, sf::ConvexShape &arrow)
{
    // Рисует и выводит один кадр
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