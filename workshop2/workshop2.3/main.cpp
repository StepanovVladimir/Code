#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <ctime>
#include <random>

struct Ball
{
    sf::CircleShape shape;
    sf::Vector2f position;
    float size;
    sf::Vector2f speed;
    sf::Color color;
};

struct PRNG
{
    std::mt19937 engine;
};

void initGenerator(PRNG &generator)
{
    unsigned device = unsigned(std::time(nullptr));
    generator.engine.seed(device);
}

float randomSpeed(PRNG &generator, float minValue, float maxValue)
{
    std::uniform_real_distribution<float> distribution(minValue, maxValue);
    return distribution(generator.engine);
}

void init(std::vector<Ball> &balls)
{
    PRNG generator;
    initGenerator(generator);
    const float minSpeed = -400;
    const float maxSpeed = 400;
    const std::vector<sf::Color> colors = {
        sf::Color(255, 255, 255),
        sf::Color(255, 0, 0),
        sf::Color(0, 255, 0),
        sf::Color(0, 0, 255),
        sf::Color(255, 255, 0),
        sf::Color(255, 0, 255),
        sf::Color(0, 255, 255)};
    std::vector<sf::Vector2f> speeds{{0, 0}};
    const std::vector<float> sizes = {30, 30, 30, 30, 30, 30, 30};
    const std::vector<sf::Vector2f> positions = {
        {80, 250},
        {720, 80},
        {720, 520},
        {400, 450},
        {720, 350},
        {80, 80},
        {80, 520}};
    for (size_t i = 0; i < 7; ++i)
    {
        float speedX = randomSpeed(generator, minSpeed, maxSpeed);
        float speedY = randomSpeed(generator, minSpeed, maxSpeed);
        speeds[i] = {speedX, speedY};
        balls[i].color = colors[i];
        balls[i].size = sizes[i];
        balls[i].speed = speeds[i];
        balls[i].position = positions[i];
        balls[i].shape.setPosition(balls[i].position);
        balls[i].shape.setOrigin(balls[i].size, balls[i].size);
        balls[i].shape.setRadius(balls[i].size);
        balls[i].shape.setFillColor(balls[i].color);
    }
}

void pollEvents(sf::RenderWindow &window)
{
    sf::Event event{};
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

void update(std::vector<Ball> &balls, float &deltaTime)
{

    for (size_t i = 0; i < 7; ++i)
    {
        for (size_t j = i + 1; j < 7; ++j)
        {
            sf::Vector2f deltaVector = balls[i].shape.getPosition() - balls[j].shape.getPosition();
            float delta = std::sqrt(std::pow(deltaVector.x, 2) + std::pow(deltaVector.y, 2));
            float distanse = balls[i].size + balls[j].size;
            if (delta <= distanse)
            {
                sf::Vector2f deltaSpeed = balls[i].speed - balls[j].speed;
                float scalarProduct = deltaSpeed.x * deltaVector.x + deltaSpeed.y * deltaVector.y;
                balls[i].speed = balls[i].speed - scalarProduct / (delta * delta) * deltaVector;
                balls[j].speed = balls[j].speed + scalarProduct / (delta * delta) * deltaVector;
            }
        }
    }
    for (size_t i = 0; i < 7; ++i)
    {
        sf::Vector2f position = balls[i].shape.getPosition();
        position += balls[i].speed * deltaTime;

        if ((position.x + balls[i].size >= 800) && (balls[i].speed.x > 0))
        {
            balls[i].speed.x = -balls[i].speed.x;
        }
        if ((position.x - balls[i].size < 0) && (balls[i].speed.x < 0))
        {
            balls[i].speed.x = -balls[i].speed.x;
        }
        if ((position.y + balls[i].size >= 600) && (balls[i].speed.y > 0))
        {
            balls[i].speed.y = -balls[i].speed.y;
        }
        if ((position.y - balls[i].size < 0) && (balls[i].speed.y < 0))
        {
            balls[i].speed.y = -balls[i].speed.y;
        }
        balls[i].shape.setPosition(position);
    }
}

void redrawFrame(sf::RenderWindow &window, std::vector<Ball> &balls)
{
    window.clear();
    for (size_t i = 0; i < 7; ++i)
    {
        window.draw(balls[i].shape);
    }
    window.display();
}

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(
        sf::VideoMode({800, 600}),
        "Balls", sf::Style::Default, settings);
    sf::Clock clock;
    std::vector<Ball> balls(7);
    init(balls);
    while (window.isOpen())
    {
        pollEvents(window);
        float deltaTime = clock.restart().asSeconds();
        update(balls, deltaTime);
        redrawFrame(window, balls);
    }
}