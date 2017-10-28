#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>

struct EyeR
{
    sf::ConvexShape ellipseR;
    sf::ConvexShape eyeBallR;
    sf::Vector2f position;
    float rotation = 0;
};

struct EyeL
{
    sf::ConvexShape ellipseL;
    sf::ConvexShape eyeBallL;
    sf::Vector2f position;
    float rotation = 0;
};

sf::Vector2f toEuclidean(float radiusX, float radiusY, float angle)
{
    return {
        radiusX * std::cos(angle),
        radiusY * std::sin(angle)};
}

void updateEyeRElements(EyeR &eyeR)
{
    eyeR.ellipseR.setPosition(eyeR.position);

    const sf::Vector2f headOffset = toEuclidean(20, 40, eyeR.rotation);
    eyeR.eyeBallR.setPosition(eyeR.position + headOffset);
}

void initEyeR(EyeR &eyeR)
{
    constexpr int pointCount = 200;
    eyeR.position = {340, 300};

    const sf::Vector2f ellipseRadius = {40.f, 80.f};
    eyeR.ellipseR.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
    eyeR.ellipseR.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        sf::Vector2f point = {
            ellipseRadius.x * std::sin(angle),
            ellipseRadius.y * std::cos(angle)};
        eyeR.ellipseR.setPoint(pointNo, point);
    }

    const sf::Vector2f eyeBallRadius = {10.f, 20.f};
    eyeR.eyeBallR.setFillColor(sf::Color(0x0, 0x0, 0x0));
    eyeR.eyeBallR.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        sf::Vector2f point = {
            eyeBallRadius.x * std::sin(angle),
            eyeBallRadius.y * std::cos(angle)};
        eyeR.eyeBallR.setPoint(pointNo, point);
    }

    updateEyeRElements(eyeR);
}

void updateEyeLElements(EyeL &eyeL)
{
    eyeL.ellipseL.setPosition(eyeL.position);

    const sf::Vector2f headOffset = toEuclidean(20, 40, eyeL.rotation);
    eyeL.eyeBallL.setPosition(eyeL.position + headOffset);
}

void initEyeL(EyeL &eyeL)
{
    constexpr int pointCount = 200;
    eyeL.position = {460, 300};

    const sf::Vector2f ellipseRadius = {40.f, 80.f};
    eyeL.ellipseL.setFillColor(sf::Color(0xFF, 0xFF, 0xFF));
    eyeL.ellipseL.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        sf::Vector2f point = {
            ellipseRadius.x * std::sin(angle),
            ellipseRadius.y * std::cos(angle)};
        eyeL.ellipseL.setPoint(pointNo, point);
    }

    const sf::Vector2f eyeBallRadius = {10.f, 20.f};
    eyeL.eyeBallL.setFillColor(sf::Color(0x0, 0x0, 0x0));
    eyeL.eyeBallL.setPointCount(pointCount);
    for (int pointNo = 0; pointNo < pointCount; ++pointNo)
    {
        float angle = float(2 * M_PI * pointNo) / float(pointCount);
        sf::Vector2f point = {
            eyeBallRadius.x * std::sin(angle),
            eyeBallRadius.y * std::cos(angle)};
        eyeL.eyeBallL.setPoint(pointNo, point);
    }

    updateEyeLElements(eyeL);
}

void onMouseMove(const sf::Event::MouseMoveEvent &event, sf::Vector2f &mousePosition)
{
    std::cout << "mouse x=" << event.x << ", y=" << event.y << std::endl;
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

void update(const sf::Vector2f &mousePosition, EyeR &eyeR, EyeL &eyeL)
{
    const sf::Vector2f deltaR = mousePosition - eyeR.position;
    eyeR.rotation = atan2(deltaR.y, deltaR.x);
    updateEyeRElements(eyeR);

    const sf::Vector2f deltaL = mousePosition - eyeL.position;
    eyeL.rotation = atan2(deltaL.y, deltaL.x);
    updateEyeLElements(eyeL);
}

void redrawFrame(sf::RenderWindow &window, EyeR &eyeR, EyeL &eyeL)
{
    window.clear();
    window.draw(eyeR.ellipseR);
    window.draw(eyeR.eyeBallR);
    window.draw(eyeL.ellipseL);
    window.draw(eyeL.eyeBallL);
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
        "Arrow follows mouse", sf::Style::Default, settings);

    EyeR eyeR;
    EyeL eyeL;
    sf::Vector2f mousePosition;

    initEyeR(eyeR);
    initEyeL(eyeL);
    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        update(mousePosition, eyeR, eyeL);
        redrawFrame(window, eyeR, eyeL);
    }
}