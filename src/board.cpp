#include <SFML/Audio.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include "../lib/board.hpp"

Board::Board() {
    // board
    white_square.setSize(Vector2f(100.f, 100.f));
    white_square.setFillColor(Color(0x908F8DFF));
    black_square.setSize(Vector2f(100.f, 100.f));
    black_square.setFillColor(Color(0x6E6D6BFF));
    // special squares
    possible_square.setRadius(25.f);
    possible_square.setFillColor(Color(0x00000040));
    selected_square.setSize(Vector2f(100.0f, 100.0f));
    selected_square.setFillColor(Color(0x7590A1FF));
    // pawn
    if (!white_pawn.loadFromFile("assets/textures/white_pawn.png"))
        std::cout << "Failed to open white_pawn.png" << std::endl;
    if (!black_pawn.loadFromFile("assets/textures/black_pawn.png"))
        std::cout << "Failed to open black_pawn.png" << std::endl;
    // knight
    if (!white_knight.loadFromFile("assets/textures/white_knight.png"))
        std::cout << "Failed to open white_knight.png" << std::endl;
    if (!black_knight.loadFromFile("assets/textures/black_knight.png"))
        std::cout << "Failed to open black_knight.png" << std::endl;
    // bishop
    if (!white_bishop.loadFromFile("assets/textures/white_bishop.png"))
        std::cout << "Failed to open white_bishop.png" << std::endl;
    if (!black_bishop.loadFromFile("assets/textures/black_bishop.png"))
        std::cout << "Failed to open black_bishop.png" << std::endl;
    //rook
    if (!white_rook.loadFromFile("assets/textures/white_rook.png"))
        std::cout << "Failed to open white_rook.png" << std::endl;
    if (!black_rook.loadFromFile("assets/textures/black_rook.png"))
        std::cout << "Failed to open black_rook.png" << std::endl;
    // queen
    if (!white_queen.loadFromFile("assets/textures/white_queen.png"))
        std::cout << "Failed to open white_queen.png" << std::endl;
    if (!black_queen.loadFromFile("assets/textures/black_queen.png"))
        std::cout << "Failed to open black_queen.png" << std::endl;
    // king
    if (!white_king.loadFromFile("assets/textures/white_king.png"))
        std::cout << "Failed to open white_king.png" << std::endl;
    if (!black_king.loadFromFile("assets/textures/black_king.png"))
        std::cout << "Failed to open black_king.png" << std::endl;

    // sound
    if (!move.loadFromFile("assets/sounds/move.flac"))
        std::cout << "Failed to open move.flac" << std::endl;
    if (!capture.loadFromFile("assets/sounds/capture.flac"))
        std::cout << "Failed to open capture.flac" << std::endl;
}

void Board::draw_white(sf::RenderTarget& window, char position[8][8], int possible[8][8], int x, int y) {
    selected_square.setPosition(Vector2f(100.f * y + 50.f, 100.f * x + 50.f));
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++) {
            if(i == x && j == y)
                window.draw(selected_square);
            else {
                if((i + j + 1) % 2) {
                    white_square.setPosition(Vector2f(j * 100.f + 50.f, i * 100.f + 50.f));
                    window.draw(white_square);
                }
                else {
                    black_square.setPosition(Vector2f(j * 100.f + 50.f, i * 100.f + 50.f));
                    window.draw(black_square);
                }
            }
            switch (position[i][j]) {
                case 'K':
                    piece.setTexture(white_king);
                    break;
                case 'Q':
                    piece.setTexture(white_queen);
                    break;
                case 'R':
                    piece.setTexture(white_rook);
                    break;
                case 'B':
                    piece.setTexture(white_bishop);
                    break;
                case 'N':
                    piece.setTexture(white_knight);
                    break;
                case 'P':
                    piece.setTexture(white_pawn);
                    break;
                case 'k':
                    piece.setTexture(black_king);
                    break;
                case 'q':
                    piece.setTexture(black_queen);
                    break;
                case 'r':
                    piece.setTexture(black_rook);
                    break;
                case 'b':
                    piece.setTexture(black_bishop);
                    break;
                case 'n':
                    piece.setTexture(black_knight);
                    break;
                case 'p':
                    piece.setTexture(black_pawn);
                    break;
            }
            if(isalpha(position[i][j])) {
                piece.setPosition(Vector2f(j * 100.f + 50.f, i * 100.f + 50.f));
                window.draw(piece);
            }
            if(possible[i][j]) {
                possible_square.setPosition(Vector2f(100.f * j + 75.f, 100.f * i + 75.f));
                window.draw(possible_square);
            }
        }
    }
}

void Board::draw_black(sf::RenderTarget& window, char position[8][8], int possible[8][8], int x, int y) {
    x = 7 - x;
    y = 7 - y;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if(i == x && j == y){
                selected_square.setPosition(Vector2f(100.f * y + 50.f, 100.f * x + 50.f));
                window.draw(selected_square);
            }
            else {
                if((i + j + 1) % 2) {
                    white_square.setPosition(Vector2f(j * 100.f + 50.f, i * 100.f + 50.f));
                    window.draw(white_square);
                }
                else {
                    black_square.setPosition(Vector2f(j * 100.f + 50.f, i * 100.f + 50.f));
                    window.draw(black_square);
                }
            }
        }
    }
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            int m = 7 - j;
            int n = 7 - i;
            switch (position[i][j]) {
                case 'K':
                    piece.setTexture(white_king);
                    break;
                case 'Q':
                    piece.setTexture(white_queen);
                    break;
                case 'R':
                    piece.setTexture(white_rook);
                    break;
                case 'B':
                    piece.setTexture(white_bishop);
                    break;
                case 'N':
                    piece.setTexture(white_knight);
                    break;
                case 'P':
                    piece.setTexture(white_pawn);
                    break;
                case 'k':
                    piece.setTexture(black_king);
                    break;
                case 'q':
                    piece.setTexture(black_queen);
                    break;
                case 'r':
                    piece.setTexture(black_rook);
                    break;
                case 'b':
                    piece.setTexture(black_bishop);
                    break;
                case 'n':
                    piece.setTexture(black_knight);
                    break;
                case 'p':
                    piece.setTexture(black_pawn);
                    break;
            }
            if(isalpha(position[i][j])) {
                piece.setPosition(Vector2f(m * 100.f + 50.f, n * 100.f + 50.f));
                window.draw(piece);
            }
            if(possible[i][j]) {
                possible_square.setPosition(Vector2f(100.f * m + 75.f, 100.f * n + 75.f));
                window.draw(possible_square);
            }
        }
    }
}

void Board::play_sound(bool c) {
    if (c)
        sound.setBuffer(capture);
    else
        sound.setBuffer(move);
    sound.play();
}
