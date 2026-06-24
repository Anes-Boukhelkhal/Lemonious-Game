#ifndef FUNCTIONS_HPP_
#define FUNCTIONS_HPP_

#include <SFML/Graphics.hpp>
#include <iostream>

int loadError (const char spriteName[]);

// Need to pass font by reference because Text objects do not store a copy of the font (local font is destroyed), so a reference is passed from main, where the font is not destroyed
sf::Text loadLevel(sf::Font &font, const char description[]);

#endif