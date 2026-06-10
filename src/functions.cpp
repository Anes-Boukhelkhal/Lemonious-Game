#include "functions.h"
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>

int loadError (const char spriteName[]) {
    std::cout << "Error: " << spriteName << " could not be loaded";
    return -1;
}
