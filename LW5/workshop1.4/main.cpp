#include <SFML\Graphics.hpp>
#include <cmath>

void init(sf::Texture &textureCat, sf::Sprite &cat,
          sf::Texture &textureLaser, sf::Sprite &laser)
{
    textureCat.loadFromFile("workshop1.4/cat.png");
    cat.setTexture(textureCat);
    cat.setOrigin(textureCat.getSize().x / 2, textureCat.getSize().y / 2);
    cat.setPosition(400, 300);

    textureLaser.loadFromFile("workshop1.4/red_pointer.png");
    laser.setTexture(textureLaser);
    laser.setOrigin(textureLaser.getSize().x / 2, textureLaser.getSize().y / 2);
}

void onMouseClick(const sf::Event::MouseButtonEvent &event, sf::Vector2f &mousePosition)
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
        case sf::Event::MouseButtonPressed:
            onMouseClick(event.mouseButton, mousePosition);
        default:
            break;
        }
    }
}

void update(const sf::Vector2f &mousePosition, sf::Sprite &cat, sf::Sprite &laser, float &dt)
{
    const sf::Vector2f delta = mousePosition - cat.getPosition();
    if (delta.x > 0)
    {
        cat.setScale(1, 1);
    }
    if (delta.x < 0)
    {
        cat.setScale(-1, 1);
    }
    float deltaDistance = std::sqrt(delta.x * delta.x + delta.y * delta.y);
    if ((delta.x != 0) && (delta.y != 0))
    {
        sf::Vector2f direction = {
            delta.x / deltaDistance,
            delta.y / deltaDistance};
        float speed = std::min(deltaDistance, 200.f * dt);
        sf::Vector2f timePosition = direction * speed;
        cat.setPosition(cat.getPosition() + timePosition);
    }

    laser.setPosition(mousePosition);
}

void redrawFrame(sf::RenderWindow &window, sf::Sprite &cat, sf::Sprite &laser)
{
    window.clear(sf::Color(0xFF, 0xFF, 0xFF));
    window.draw(cat);
    window.draw(laser);
    window.display();
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Cat");
    sf::Clock clock;

    sf::Texture textureCat;
    sf::Sprite cat;
    sf::Texture textureLaser;
    sf::Sprite laser;

    sf::Vector2f mousePosition = {400, 300};

    init(textureCat, cat, textureLaser, laser);
    while (window.isOpen())
    {
        pollEvents(window, mousePosition);
        float dt = clock.restart().asSeconds();
        update(mousePosition, cat, laser, dt);
        redrawFrame(window, cat, laser);
    }
}