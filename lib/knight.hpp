#include <iostream>
#include <SFML/Graphics.hpp>

class Knight {
    sf::Texture texture_white;
    sf::Texture texture_black;
    sf::Sprite sprite;
    public:
    Knight();
    void draw(sf::RenderTarget& window, bool color, char letter, int number);
};
