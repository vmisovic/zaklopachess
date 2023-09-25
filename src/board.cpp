#include "../lib/board.hpp"

Board::Board() {
    //board
    white = Color(0xf3bc7aff);
    black = Color(0xeeeed2ff);
    for (int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            bool color = (i + j + 1) % 2;
            squares[i][j].setPosition(Vector2f( j*128.f , i*128.f ));
            squares[i][j].setSize(Vector2f(128.f, 128.f));
            squares[i][j].setFillColor(color ? Color(0xf3bc7aff) : Color(0xae722bff));
        }
    }

    possible_square.setRadius(32.f);
    possible_square.setFillColor(sf::Color(255, 0, 0, 192));
    selected_square.setSize(sf::Vector2f(128.0f,128.0f));
    selected_square.setFillColor(sf::Color(0, 0, 255, 192));
    // pawn
    if (!white_pawn.loadFromFile("assets/white_pawn.png")){
        std::cout << "Failed to open white_pawn.png" << std::endl;
    }
    if (!black_pawn.loadFromFile("assets/black_pawn.png")){
        std::cout << "Failed to open black_pawn.png" << std::endl;
    }
    // knight
    if (!white_knight.loadFromFile("assets/white_knight.png")){
        std::cout << "Failed to open white_knight.png" << std::endl;
    }
    if (!black_knight.loadFromFile("assets/black_knight.png")){
        std::cout << "Failed to open black_knight.png" << std::endl;
    }
    // bishop
    if (!white_bishop.loadFromFile("assets/white_bishop.png")){
        std::cout << "Failed to open white_bishop.png" << std::endl;
    }
    if (!black_bishop.loadFromFile("assets/black_bishop.png")){
        std::cout << "Failed to open black_bishop.png" << std::endl;
    }
    //rook
    if (!white_rook.loadFromFile("assets/white_rook.png")){
        std::cout << "Failed to open white_rook.png" << std::endl;
    }
    if (!black_rook.loadFromFile("assets/black_rook.png")){
        std::cout << "Failed to open black_rook.png" << std::endl;
    }
    // queen
    if (!white_queen.loadFromFile("assets/white_queen.png")){
        std::cout << "Failed to open white_queen.png" << std::endl;
    }
    if (!black_queen.loadFromFile("assets/black_queen.png")){
        std::cout << "Failed to open black_queen.png" << std::endl;
    }
    // king
    if (!white_king.loadFromFile("assets/white_king.png")){
        std::cout << "Failed to open white_king.png" << std::endl;
    }
    if (!black_king.loadFromFile("assets/black_king.png")){
        std::cout << "Failed to open black_king.png" << std::endl;
    }
}

void Board::draw(sf::RenderTarget& window, char position[8][8], int possible[8][8], int selected_x, int selected_y) {
    selected_square.setPosition(Vector2f( 128.f * selected_y, 128.f * selected_x));
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++) {
            if(i == selected_x && j == selected_y)
                window.draw(selected_square);
            else
                window.draw(squares[i][j]);
            switch ( position[i][j] ) {
                case 'K':
                    piece.setTexture(white_king);
                    piece.setPosition(Vector2f( j * 128.f, i * 128.f));
                    window.draw(piece);
                    break;
                case 'Q':
                    piece.setTexture(white_queen);
                    piece.setPosition(Vector2f( j * 128.f, i * 128.f));
                    window.draw(piece);
                    break;
                case 'R':
                    piece.setTexture(white_rook);
                    piece.setPosition(Vector2f( j * 128.f, i * 128.f));
                    window.draw(piece);
                    break;
                case 'B':
                    piece.setTexture(white_bishop);
                    piece.setPosition(Vector2f( j * 128.f, i * 128.f));
                    window.draw(piece);
                    break;
                case 'N':
                    piece.setTexture(white_knight);
                    piece.setPosition(Vector2f( j * 128.f, i * 128.f));
                    window.draw(piece);
                    break;
                case 'P':
                    piece.setTexture(white_pawn);
                    piece.setPosition(Vector2f( j * 128.f, i * 128.f));
                    window.draw(piece);
                    break;
                case 'k':
                    piece.setTexture(black_king);
                    piece.setPosition(Vector2f( j * 128.f, i * 128.f));
                    window.draw(piece);
                    break;
                case 'q':
                    piece.setTexture(black_queen);
                    piece.setPosition(Vector2f( j * 128.f, i * 128.f));
                    window.draw(piece);
                    break;
                case 'r':
                    piece.setTexture(black_rook);
                    piece.setPosition(Vector2f( j * 128.f, i * 128.f));
                    window.draw(piece);
                    break;
                case 'b':
                    piece.setTexture(black_bishop);
                    piece.setPosition(Vector2f( j * 128.f, i * 128.f));
                    window.draw(piece);
                    break;
                case 'n':
                    piece.setTexture(black_knight);
                    piece.setPosition(Vector2f( j * 128.f, i * 128.f));
                    window.draw(piece);
                    break;
                case 'p':
                    piece.setTexture(black_pawn);
                    piece.setPosition(Vector2f( j * 128.f, i * 128.f));
                    window.draw(piece);
                    break;
            }
            if(possible[i][j]) {
                possible_square.setPosition(Vector2f( 128.f * j + 32.f, 128.f * i + 32.f));
                window.draw(possible_square);
            }
        }
    }
}
