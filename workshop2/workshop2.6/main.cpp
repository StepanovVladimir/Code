#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <random>

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;
constexpr unsigned BALL_RADIUS = 30;
constexpr float MAX_SPEED = 500;

struct Ball
{
    sf::CircleShape shape;
    sf::Vector2f speed;
    sf::Clock clock;
    float time = 0;
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

size_t randomIndex(PRNG &generator, size_t minValue, size_t maxValue)
{
    std::uniform_int_distribution<size_t> distribution(minValue, maxValue);
    return distribution(generator.engine);
}

void init(std::vector<Ball> &balls, sf::Vector2f &mousePosition, PRNG &generator)
{
    Ball ball;
    balls.push_back(ball);
    float speedX = randomSpeed(generator, -MAX_SPEED, MAX_SPEED);
    float speedY = randomSpeed(generator, -MAX_SPEED, MAX_SPEED);
    std::vector<sf::Color> colors = {
        sf::Color(255, 255, 255),
        sf::Color(255, 0, 0),
        sf::Color(0, 255, 0),
        sf::Color(0, 0, 255),
        sf::Color(255, 255, 0),
        sf::Color(0, 255, 255),
        sf::Color(190, 64, 255),
        sf::Color(127, 127, 0)};
    sf::Color color;
    color.r = (colors[randomIndex(generator, 0, 7)].r + colors[randomIndex(generator, 0, 7)].r) / 2;
    color.g = (colors[randomIndex(generator, 0, 7)].g + colors[randomIndex(generator, 0, 7)].g) / 2;
    color.b = (colors[randomIndex(generator, 0, 7)].b + colors[randomIndex(generator, 0, 7)].b) / 2;
    size_t i = balls.size() - 1;
    balls[i].speed = {speedX, speedY};
    balls[i].shape.setPosition(mousePosition);
    balls[i].shape.setOrigin(BALL_RADIUS, BALL_RADIUS);
    balls[i].shape.setRadius(BALL_RADIUS);
    balls[i].shape.setFillColor(color);
}

void onMouseClick(const sf::Event::MouseButtonEvent &event, sf::Vector2f &mousePosition)
{
    mousePosition = {float(event.x), float(event.y)};
}

bool checkNotOverlap(std::vector<Ball> &balls, sf::Vector2f &mousePosition)
{
    bool flag = true;
    for (size_t j = 0; j < balls.size(); ++j)
    {
        sf::Vector2f deltaVector = balls[j].shape.getPosition() - mousePosition;
        float delta = std::sqrt(std::pow(deltaVector.x, 2) + std::pow(deltaVector.y, 2));
        if (delta <= 2 * BALL_RADIUS)
        {
            flag = false;
        }
    }
    return flag;
}

void pollEvents(sf::RenderWindow &window, sf::Vector2f &mousePosition, std::vector<Ball> &balls,
    PRNG &generator)
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
            if (checkNotOverlap(balls, mousePosition) || (balls.size() == 0))
            {
                init(balls, mousePosition, generator);
            }
        default:
            break;
        }
    }
}

bool isBallLifetimeEnded(Ball ball)
{
    return (ball.time >= 10);
}

void removeDeathBalls(std::vector<Ball> &balls)
{
    auto newEnd = std::remove_if(balls.begin(), balls.end(), isBallLifetimeEnded);
    balls.erase(newEnd, balls.end());
}

void updateBallLifetimes(std::vector<Ball> &balls, size_t &i)
{
    balls[i].time = balls[i].clock.getElapsedTime().asSeconds();
}

void checkBallsClash(std::vector<Ball> &balls)
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
}

void update(std::vector<Ball> &balls, float &deltaTime)
{
    removeDeathBalls(balls);
    checkBallsClash(balls);
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
        updateBallLifetimes(balls, i);
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
    PRNG generator;
    initGenerator(generator);
    while (window.isOpen())
    {
        pollEvents(window, mousePosition, balls, generator);
        float deltaTime = clock.restart().asSeconds();
        update(balls, deltaTime);
        redrawFrame(window, balls);
    }
}