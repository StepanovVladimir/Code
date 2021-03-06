#include <SFML/Graphics.hpp>
#include <vector>

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;
constexpr unsigned BALL_RADIUS = 40;

struct Ball
{
    sf::CircleShape shape;
    sf::Vector2f speed;
};

void init(std::vector<Ball> &balls)
{
    const std::vector<sf::Color> colors = {
        sf::Color(255, 0, 0),
        sf::Color(0, 255, 0),
        sf::Color(0, 0, 255),
        sf::Color(255, 255, 0)};
    const std::vector<sf::Vector2f> speeds = {
        {100.f, 100.f},
        {-150.f, 150.f},
        {200.f, -200.f},
        {-250.f, -250.f}};
    const std::vector<sf::Vector2f> positions = {
        {80, 80},
        {600, 80},
        {200, 375},
        {500, 450}};
    for (size_t i = 0; i < 4; ++i)
    {
        balls[i].speed = speeds[i];
        balls[i].shape.setPosition(positions[i]);
        balls[i].shape.setOrigin(BALL_RADIUS, BALL_RADIUS);
        balls[i].shape.setRadius(BALL_RADIUS);
        balls[i].shape.setFillColor(colors[i]);
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
    for (size_t i = 0; i < 4; ++i)
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
    for (size_t i = 0; i < 4; ++i)
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
    std::vector<Ball> balls(4);
    init(balls);
    while (window.isOpen())
    {
        pollEvents(window);
        float deltaTime = clock.restart().asSeconds();
        update(balls, deltaTime);
        redrawFrame(window, balls);
    }
}