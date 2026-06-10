#include <SFML/Graphics.hpp>
#include "functions.cpp"
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>


// Made using SFML 3.1.0 library //
// All sprites are generated using ChatGPT // 

int main () {
    srand(time(NULL));

    // Window setup //
    const int width = 1920;
    const int height = 1080;
    sf::Vector2u windowDimensions = {width, height};
    sf::RenderWindow window(sf::VideoMode( {width, height} ), "Lemon Game!", sf::State::Fullscreen);
    window.setFramerateLimit(144);

    // Sprites setup // 
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("assets/background.png")) {
       loadError("background");
    } 
    sf::Sprite backgroundSprite(backgroundTexture);
    backgroundSprite.setScale ( {1.15f, 1.15f} );
    
    sf::Texture treeTexture;
    if (!treeTexture.loadFromFile("assets/tree.png") ){
        loadError("tree");
    }
    sf::Sprite treeSprite(treeTexture);
    treeSprite.setScale( {0.85f, 0.85f} );
    treeSprite.setPosition( {560.0f, 190.0f} );

    
    sf::Texture lemonTexture;
    if (!lemonTexture.loadFromFile("assets/lemon.png")) {
        loadError("lemon");
    }
    const unsigned int numLemons = 12;
    std::vector<sf::Sprite> lemonSprites;
    sf::Sprite lemonSprite(lemonTexture);
    lemonSprite.setScale( {0.10, 0.10} );

    //FIXME: want lemons to be placed only within boundaries of the tree sprite, and also without overlapping with each other
    for (unsigned int i = 0; i < numLemons; ++i) {
        float lemonXPos = static_cast<float> (rand () % (380) + 700);
        float lemonYPos = static_cast<float> (rand () % (200) + 350);
        lemonSprite.setPosition ( {lemonXPos, lemonYPos} );
        lemonSprites.push_back(lemonSprite);
    }


    
    // Running the window // 
    while (window.isOpen()) {

        // Polling events //
        while (const std::optional event = window.pollEvent()) {
            
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if ( auto *keyPress = event->getIf<sf::Event::KeyPressed>() ) {
                if (keyPress->scancode == sf::Keyboard::Scancode::Escape) {
                window.close();
                }
            }
        }



        window.clear(sf::Color(63, 215, 253));
        
        window.draw(backgroundSprite);
        window.draw(treeSprite);
         
        for (unsigned int i = 0; i < numLemons; ++i) {
                if (lemonSprites[i].getPosition().y == 800.0) {
                    continue;
                }
                else {
                    lemonSprites[i].move( {0.0f, 0.5f} );
                }
        }

        for (unsigned int i = 0; i < numLemons; ++i) {
            window.draw(lemonSprites[i]);
        }

        window.display();

    }
    
    return 0;

}