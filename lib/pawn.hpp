#include <iostream>
#include <SFML/Graphics.hpp>

class Pawn {
    sf::Texture texture_white;
    sf::Texture texture_black;
    sf::Sprite sprite;
    public:
    Pawn();
    void draw(sf::RenderTarget& window, bool color, char letter, int number);
};
