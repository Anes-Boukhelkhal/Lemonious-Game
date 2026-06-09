#include <iostream>
#include <filesystem>
#include <SFML/Graphics.hpp>

// Made using SFML 3.1.0 library

int main () {
    std::cout << std::filesystem::current_path();
    // Window setup //
    const int width = 1920;
    const int height = 1080;
    sf::Vector2u windowDimensions = {width, height};
    sf::RenderWindow window(sf::VideoMode( {width, height} ), "Lemon Game!");
    window.setFramerateLimit(144);

    // Sprites setup // 
    sf::Texture texture;
    if (!texture.loadFromFile("assets/tree.png") ){
        std::cerr << "ERROR: Tree texture could not be loaded";
        return -1;
    }
    sf::Sprite treeSprite(texture);
    treeSprite.setScale( {0.25f, 0.25f} );
    treeSprite.setPosition( {width/2.0, height/2.0f} );
    

    // Running the window // 
    while (window.isOpen()) {
        
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
        
        window.draw(treeSprite);

        window.display();

    }
    
    return 0;

}