#include "include/functions.hpp"
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

int loadError (const char assetName[]) {
    std::cout << "Error: " << assetName << " could not be loaded";
    return -1;
}

sf::Text loadLevel(sf::Font &font, const char description[]) {
    sf::Text levelComplete(font);
    levelComplete.setString(description);
    levelComplete.setCharacterSize(60);
    levelComplete.setFillColor(sf::Color::Black);
    levelComplete.setPosition( {550.0f, 150.0f});

    return levelComplete;
}


