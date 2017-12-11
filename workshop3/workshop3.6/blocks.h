#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include "random.h"

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;

struct Block
{
    sf::RectangleShape shape;
    float speed = 0;
    float speedup = 500;
    bool stop;
};

void update(std::vector<Block>& blocks, float& deltaTime, PRNG &generator);