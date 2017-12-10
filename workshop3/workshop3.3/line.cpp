#include "line.h"

void initializeLine(sf::VertexArray& line, sf::RectangleShape& square)
{
    line[0].position = CENTER; 
    line[0].color = sf::Color(0, 0, 0);
    line[1].color = sf::Color(0, 0, 0);
    square.setSize({4, 4});
    square.setOrigin({2, 2});
    square.setPosition(CENTER);
    square.setFillColor(sf::Color(0, 0, 0));
}

void updateLine(sf::VertexArray& line, sf::Vector2f& mousePosition)
{
    line[1].position = mousePosition;
}