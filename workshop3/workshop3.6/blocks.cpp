#include "blocks.h"

constexpr unsigned OUTLINE_THICKNESS = 2;

void init(std::vector<Block>& blocks, PRNG& generator, size_t& i)
{
    Block block;
    blocks.push_back(block);
    const float minSize = 10;
    const float maxSize = 100;
    i++;
    blocks[i].shape.setPosition({random(generator, 0, WINDOW_WIDTH), 0});
    blocks[i].shape.setSize({random(generator, minSize, maxSize), random(generator, minSize, maxSize)});
    blocks[i].shape.setOrigin({blocks[i].shape.getSize().x / 2, 0});
    blocks[i].shape.setFillColor(sf::Color(255, 0, 0));
    blocks[i].shape.setOutlineColor(sf::Color(0, 0, 0));
    blocks[i].shape.setOutlineThickness(OUTLINE_THICKNESS);
    blocks[i].stop = false;
}

void checkCollision(sf::Vector2f& position, std::vector<Block>& blocks, size_t& i)
{
    if (position.y + blocks[i].shape.getSize().y + OUTLINE_THICKNESS >= WINDOW_HEIGHT)
    {
        blocks[i].speed = 0;
        blocks[i].speedup = 0;
        blocks[i].stop = true;
    }
    for (size_t j = 0; j < blocks.size() - 1; ++j)
    {
        if ((position.x + blocks[i].shape.getOrigin().x + OUTLINE_THICKNESS > blocks[j].shape.getPosition().x - blocks[j].shape.getOrigin().x) &&
            (position.x - blocks[i].shape.getOrigin().x - OUTLINE_THICKNESS < blocks[j].shape.getPosition().x + blocks[j].shape.getOrigin().x) &&
            (position.y + blocks[i].shape.getSize().y + OUTLINE_THICKNESS >= blocks[j].shape.getPosition().y))
        {
            blocks[i].speed = 0;
            blocks[i].speedup = 0;
            blocks[i].stop = true;
        }
    }
}

void update(std::vector<Block>& blocks, float& deltaTime, PRNG &generator)
{
    size_t i = blocks.size() - 1;
    if ((blocks.size() == 0) || (blocks[i].stop))
    {
        init(blocks, generator, i);
    }
    sf::Vector2f position = blocks[i].shape.getPosition();
    blocks[i].speed += blocks[i].speedup * deltaTime;
    position.y += blocks[i].speed * deltaTime;
    checkCollision(position, blocks, i);
    blocks[i].shape.setPosition(position);
}