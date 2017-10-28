#include <SFML\Graphics.hpp>

void init(sf::Texture &textureCat, sf::Sprite &cat)
{
    textureCat.loadFromFile("workshop1.3/cat.png");
    cat.setTexture(textureCat);
    cat.setPosition(400, 300);
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

void redrawFrame(sf::RenderWindow &window, sf::Sprite &cat)
{
    window.clear(sf::Color(0xFF, 0xFF, 0xFF));
    window.draw(cat);
    window.display();
}

int main()
{
    constexpr unsigned WINDOW_WIDTH = 800;
    constexpr unsigned WINDOW_HEIGHT = 600;

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Cat");

    sf::Texture textureCat;
    sf::Sprite cat;

    init(textureCat, cat);
    while (window.isOpen())
    {
        pollEvents(window);
        redrawFrame(window, cat);
    }
}