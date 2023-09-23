#include <iostream>
#include <SFML/Graphics.hpp>

class Queen {
    sf::Texture texture_white;
    sf::Texture texture_black;
    sf::Sprite sprite;
    public:
    Queen();
    void draw(sf::RenderTarget& window, bool color, char letter, int number);
};
