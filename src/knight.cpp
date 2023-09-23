#include "../lib/knight.hpp"

Knight::Knight() {
    if (!texture_white.loadFromFile("assets/white_knight.png")){
        std::cout << "Failed to open white_knight.png" << std::endl;
    }
    if (!texture_black.loadFromFile("assets/black_knight.png")){
        std::cout << "Failed to open black_knight.png" << std::endl;
    }
    texture_white.setSmooth(true);
    texture_black.setSmooth(true);
}

void Knight::draw(sf::RenderTarget& window, bool color, char letter, int number) {
    if(color)
        sprite.setTexture(texture_white);
    else
        sprite.setTexture(texture_black);
    sprite.setPosition(sf::Vector2f( (letter - 65) * 128.f, (8 - number) * 128.f));
    window.draw(sprite);
}
