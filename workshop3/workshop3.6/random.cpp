#include "random.h"

void initGenerator(PRNG &generator)
{
    unsigned seed = unsigned(std::time(nullptr));
    generator.engine.seed(seed);
}

float random(PRNG &generator, float minValue, float maxValue)
{
    std::uniform_real_distribution<float> distribution(minValue, maxValue);
    return distribution(generator.engine);
}