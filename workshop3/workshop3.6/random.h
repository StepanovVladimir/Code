#pragma once

#include <random>
#include <ctime>

struct PRNG
{
    std::mt19937 engine;
};

void initGenerator(PRNG &generator);
float random(PRNG &generator, float minValue, float maxValue);