#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <random>

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;
constexpr unsigned BALL_RADIUS = 30;

struct Ball
{
    sf::CircleShape shape;
    sf::Vector2f speed;
};

struct PRNG
{
    std::mt19937 engine;
};

void initGenerator(PRNG &generator)
{
    unsigned seed = unsigned(std::time(nullptr));
    generator.engine.seed(seed);
}

float randomSpeed(PRNG &generator, float minValue, float maxValue)
{
    std::uniform_real_distribution<float> distribution(minValue, maxValue);
    return distribution(generator.engine);
}

size_t randomColor(PRNG &generator, size_t minValue, size_t maxValue)
{
    std::uniform_int_distribution<size_t> distribution(minValue, maxValue);
    return distribution(generator.engine);
}

void init(std::vector<Ball> &balls, sf::Vector2f &mousePosition)
{
    unsigned flag = 0;
    for (size_t j = 0; j < balls.size(); ++j)
    {
        sf::Vector2f deltaVector = balls[j].shape.getPosition() - mousePosition;
        float delta = std::sqrt(std::pow(deltaVector.x, 2) + std::pow(deltaVector.y, 2));
        if (delta <= 2 * BALL_RADIUS)
        {
            flag = 1;
        }
    }
    if ((flag == 0) || (balls.size() == 0))
    {
        Ball ball;
        balls.push_back(ball);
        PRNG generator;
        initGenerator(generator);
        const float minSpeed = -400;
        const float maxSpeed = 400;
        sf::Color color;
        std::vector<sf::Color> colors = {
            sf::Color(255, 255, 255),
            sf::Color(255, 0, 0),
            sf::Color(0, 255, 0),
            sf::Color(0, 0, 255),
            sf::Color(255, 255, 0),
            sf::Color(0, 255, 255),
            sf::Color(190, 64, 255),
            sf::Color(127, 127, 0)};
        size_t i = balls.size() - 1;
        float speedX = randomSpeed(generator, minSpeed, maxSpeed);
        float speedY = randomSpeed(generator, minSpeed, maxSpeed);
        size_t j = randomColor(generator, 0, 7);
        size_t k = randomColor(generator, 0, 7);
        color.r = (colors[j].r + colors[k].r) / 2;
        color.g = (colors[j].g + colors[k].g) / 2;
        color.b = (colors[j].b + colors[k].b) / 2;
        balls[i].speed = {speedX, speedY};
        balls[i].shape.setPosition(mousePosition);
        balls[i].shape.setOrigin(BALL_RADIUS, BALL_RADIUS);
        balls[i].shape.setRadius(BALL_RADIUS);
        balls[i].shape.setFillColor(color);
    }   
}

void onMouseClick(const sf::Event::MouseButtonEvent &event, sf::Vector2f &mousePosition)
{
    mousePosition = {float(event.x), float(event.y)};
}

void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition, std::vector<Ball> &balls)
{
    sf::Event event{};
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
        case sf::Event::Closed:
            window.close();
            break;
        case sf::Event::MouseButtonPressed:
            onMouseClick(event.mouseButton, mousePosition);
            init(balls, mousePosition);
        default:
            break;
        }
    }
}

void update(std::vector<Ball> &balls, float &deltaTime)
{

    for (size_t i = 0; i < balls.size(); ++i)
    {
        for (size_t j = i + 1; j < balls.size(); ++j)
        {
            sf::Vector2f deltaVector = balls[i].shape.getPosition() - balls[j].shape.getPosition();
            float delta = std::sqrt(std::pow(deltaVector.x, 2) + std::pow(deltaVector.y, 2));
            float distanse = 2 * BALL_RADIUS;
            if (delta <= distanse)
            {
                sf::Vector2f deltaSpeed = balls[i].speed - balls[j].speed;
                float scalarProduct = deltaSpeed.x * deltaVector.x + deltaSpeed.y * deltaVector.y;
                balls[i].speed = balls[i].speed - scalarProduct / float(std::pow(delta, 2)) * deltaVector;
                balls[j].speed = balls[j].speed + scalarProduct / float(std::pow(delta, 2)) * deltaVector;
            }
        }
    }
    for (size_t i = 0; i < balls.size(); ++i)
    {
        sf::Vector2f position = balls[i].shape.getPosition();
        position += balls[i].speed * deltaTime;

        if ((position.x + BALL_RADIUS >= WINDOW_WIDTH) && (balls[i].speed.x > 0))
        {
            balls[i].speed.x = -balls[i].speed.x;
        }
        if ((position.x - BALL_RADIUS < 0) && (balls[i].speed.x < 0))
        {
            balls[i].speed.x = -balls[i].speed.x;
        }
        if ((position.y + BALL_RADIUS >= WINDOW_HEIGHT) && (balls[i].speed.y > 0))
        {
            balls[i].speed.y = -balls[i].speed.y;
        }
        if ((position.y - BALL_RADIUS < 0) && (balls[i].speed.y < 0))
        {
            balls[i].speed.y = -balls[i].speed.y;
        }
        balls[i].shape.setPosition(position);
    }
}

void redrawFrame(sf::RenderWindow &window, std::vector<Ball> &balls)
{
    window.clear();
    for (size_t i = 0; i < balls.size(); ++i)
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
        sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Balls", sf::Style::Default, settings);
    sf::Clock clock;
    std::vector<Ball> balls;
    sf::Vector2f mousePosition;
    while (window.isOpen())
    {
        pollEvents(window, mousePosition, balls);
        float deltaTime = clock.restart().asSeconds();
        update(balls, deltaTime);
        redrawFrame(window, balls);
    }
}