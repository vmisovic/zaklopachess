#include <iostream>
#include <SFML/Graphics.hpp>

class Rook {
    sf::Texture texture_white;
    sf::Texture texture_black;
    sf::Sprite sprite;
    public:
    Rook();
    void draw(sf::RenderTarget& window, bool color, char letter, int number);
};
