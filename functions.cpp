#include "functions.hpp"
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

int loadError (const char assetName[]) {
    std::cout << "Error: " << assetName << " could not be loaded";
    return -1;
}


