#include "../lib/board.hpp"

Board::Board() {
    white = sf::Color(0xf3bc7aff);
    black = sf::Color(0xeeeed2ff);

    for (int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            bool color = (((i + j) % 2) == 0) ? true : false;
            squares[i][j].setPosition(sf::Vector2f( j*128.f , i*128.f ));
            squares[i][j].setSize(sf::Vector2f(128.f, 128.f));
            squares[i][j].setFillColor(color ? sf::Color(0xf3bc7aff) : sf::Color(0xae722bff));
        }
    }
}

void Board::draw(sf::RenderTarget& window) {
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            window.draw(squares[i][j]);
        }
    }
}
