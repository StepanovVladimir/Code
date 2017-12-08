#include "ball.h"
#include "text.h"

void handleEvents(sf::RenderWindow& window)
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
        }
    }
}

void render(sf::RenderWindow& window, sf::CircleShape& shape, sf::Text& text)
{
    window.clear(sf::Color(0xFF, 0xFF, 0xFF));
    window.draw(shape);
    window.draw(text);
    window.display();
}

int main()
{
    sf::RenderWindow window;
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    window.create(
        sf::VideoMode(800, 600),
        "Name ball", sf::Style::Default, settings);
    sf::CircleShape shape;
    sf::Font font;
    sf::Text text;
    initializeBall(shape);
    initializeText(font, text);
    while (window.isOpen())
    {
        handleEvents(window);
        render(window, shape, text);
    }
    return 0;
}