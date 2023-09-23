#include <iostream>
#include <SFML/Graphics.hpp>

class King {
    sf::Texture texture_white;
    sf::Texture texture_black;
    sf::Sprite sprite;
    public:
    King();
    void draw(sf::RenderTarget& window, bool color, char letter, int number);
};
