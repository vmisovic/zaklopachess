#include "../lib/pawn.hpp"

Pawn::Pawn() {
    if (!texture_white.loadFromFile("assets/white_pawn.png")){
        std::cout << "Failed to open white_pawn.png" << std::endl;
    }
    if (!texture_black.loadFromFile("assets/black_pawn.png")){
        std::cout << "Failed to open black_pawn.png" << std::endl;
    }
    texture_white.setSmooth(true);
    texture_black.setSmooth(true);
}

void Pawn::draw(sf::RenderTarget& window, bool color, char letter, int number) {
    if(color)
        sprite.setTexture(texture_white);
    else
        sprite.setTexture(texture_black);
    sprite.setPosition(sf::Vector2f( (letter - 65) * 128.f, (8 - number) * 128.f));
    window.draw(sprite);
}
