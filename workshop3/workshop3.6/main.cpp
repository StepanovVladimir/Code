#include "blocks.h"

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

void redrawFrame(sf::RenderWindow& window, std::vector<Block>& blocks)
{
    window.clear(sf::Color(0xFF, 0xFF, 0xFF));
    for (auto& block : blocks)
    {
        window.draw(block.shape);
    }
    window.display();
}

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode({WINDOW_WIDTH, WINDOW_HEIGHT}),
        "Blocks", sf::Style::Default, settings);
    sf::Clock clock;
    std::vector<Block> blocks;
    PRNG generator;
    initGenerator(generator);
    while (window.isOpen())
    {
        pollEvents(window);
        float deltaTime = clock.restart().asSeconds();
        update(blocks, deltaTime, generator);
        redrawFrame(window, blocks);
    }
}