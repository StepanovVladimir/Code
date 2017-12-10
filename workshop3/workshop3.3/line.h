#pragma once

#include <SFML/Graphics.hpp>

constexpr unsigned WINDOW_WIDTH = 800;
constexpr unsigned WINDOW_HEIGHT = 600;
static const sf::Vector2f CENTER = {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2};

void initializeLine(sf::VertexArray& line, sf::RectangleShape& square);
void updateLine(sf::VertexArray& line, sf::Vector2f& mousePosition);