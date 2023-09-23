#include <iostream>
#include <SFML/Graphics.hpp>

class Bishop {
    sf::Texture texture_white;
    sf::Texture texture_black;
    sf::Sprite sprite;
    public:
    Bishop();
    void draw(sf::RenderTarget& window, bool color, char letter, int number);
};
