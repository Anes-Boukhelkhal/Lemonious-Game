#include <SFML/Graphics.hpp>
#include "include/functions.hpp"
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <string>


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
    unsigned int numLemons = 12;
    std::vector<sf::Sprite> lemonSprites;
    sf::Sprite lemonSprite(lemonTexture);
    lemonSprite.setScale( {0.10, 0.10} );

    sf::Texture basketTexture;
    if (!basketTexture.loadFromFile("assets/basket.png")) {
        loadError("basket");
    }
    sf::Sprite basketSprite(basketTexture);
    basketSprite.setOrigin( {512.0f, 512.0f} );
    basketSprite.setScale( {0.20f, 0.20f });
    basketSprite.setPosition( {800.0f, 800.0f} );



    // Score counter //
    sf::Font font;
    if (!font.openFromFile("assets/PressStart2P-Regular.ttf")) {
        loadError("Font");
    }
    sf::Text scoreText(font);
    
    scoreText.setCharacterSize(100);
    scoreText.setFillColor(sf::Color::Black);
    scoreText.setPosition( {600.0f, 50.0f} );
    unsigned int scoreCounter = 0;



    // Levels Completion Display //
    // FIXME: Tried to make a function to be used for multiple levels, but getting an arithemtic exception thrown when drawing the returned sf::Text object
    sf::Text levelOneComplete(font);
    levelOneComplete.setString("Level 1 Complete!\nPress [2] to continue");
    levelOneComplete.setCharacterSize(60);
    levelOneComplete.setFillColor(sf::Color::Black);
    levelOneComplete.setPosition( {550.0f, 150.0f});
    
    bool gameStarted = false;
    bool levelOne = false;
    bool levelTwo = false;


    

    // FIXME: want lemons to be placed only within boundaries of the tree sprite, and also without overlapping with each other
    for (unsigned int i = 0; i < numLemons; ++i) {
        float lemonXPos = static_cast<float> (rand () % (380) + 700);
        float lemonYPos = static_cast<float> (rand () % (200) + 350);
        lemonSprite.setPosition ( {lemonXPos, lemonYPos} );
        lemonSprites.push_back(lemonSprite);
    }

    bool lemonLanded[numLemons] = {}; // all values initialized to 0 (false), this bool array is used so that the score is incremented once after each lemon lands, not once per frame

    
    // Running the window loop // 
    while (window.isOpen()) {

        // Event polling loop //
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

        // Basket moves horizontally //
        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
            float cursorXPosition = static_cast<float> (sf::Mouse::getPosition(window).x);
            basketSprite.setPosition( {cursorXPosition, 800.0f } );
        }

        sf::FloatRect basketHitbox( {basketSprite.getPosition().x, basketSprite.getPosition().y}, {5, 5} );

        window.clear(sf::Color(63, 215, 253));
        window.draw(backgroundSprite);
        window.draw(treeSprite);
                
        sf::Text introText(font);
        introText.setCharacterSize(50);
        introText.setFillColor(sf::Color::Black);
        introText.setPosition( {580.0f, 50.0f} );
        introText.setString("Welcome to Lemonious!\nPress Space to Start"); 
        if (!gameStarted) {
            window.draw(introText);
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Space)) {
            gameStarted = true;
            levelOne = true;
        }

        // FIXME: Add an option to restart the game if level one failed (and for subsequent levels)
        if (levelOne) { 
            for (unsigned int i = 0; i < numLemons; ++i) {

                if (lemonSprites[i].getPosition().y == 800.0f ) {
                continue;
                }

                else {
                lemonSprites[i].move( {0.0f, 0.5f} );
                scoreText.setString("Score: " + std::to_string(scoreCounter));
                }

            }

            for (unsigned int i = 0; i < numLemons; ++i) {
                if (lemonSprites[i].getPosition().y == 800.0f) {
                    continue;
                }
                if (lemonSprites[i].getGlobalBounds().findIntersection(basketHitbox) && lemonLanded[i] == false){
                    lemonLanded[i] = true;
                    ++scoreCounter;
                    scoreText.setString("Score: " + std::to_string(scoreCounter));
                }
            }

            for (unsigned int i = 0; i < numLemons; ++i) {
                if (!lemonLanded[i] && lemonSprites[i].getPosition().y != 800.0f ) {
                    window.draw(lemonSprites[i]);
                }
            }

            window.draw(scoreText);

            if (scoreCounter == 12) {
                window.draw(levelOneComplete);

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Num2)) {
                    levelOne = false;
                    levelTwo = true;

                }
            }
                
        }

        else if (levelTwo) {
            scoreCounter = 0;
            scoreText.setString("Score: " + std::to_string(scoreCounter));
            window.draw(scoreText);
        }



            window.draw(basketSprite);
            window.display();

        }
    
    return 0;

}