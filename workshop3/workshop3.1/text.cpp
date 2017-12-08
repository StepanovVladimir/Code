#include "text.h"

void initializeText(sf::Font& font, sf::Text& text)
{
    if (font.loadFromFile("arialn.ttf"))
    {
        text.setFont(font);
        text.setString("SVP");
        text.setCharacterSize(50);
        text.setFillColor(sf::Color(0, 0, 0));
        text.setPosition({360, 280});
    }
}