#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

using namespace sf;

class Board {
    private:
    Texture white_pawn;
    Texture black_pawn;
    Texture white_knight;
    Texture black_knight;
    Texture white_bishop;
    Texture black_bishop;
    Texture white_rook;
    Texture black_rook;
    Texture white_queen;
    Texture black_queen;
    Texture white_king;
    Texture black_king;
    Sprite piece;

    CircleShape possible_square;
    RectangleShape selected_square;

    RectangleShape squares[8][8];
    RectangleShape white_square;
    RectangleShape black_square;

    SoundBuffer move;
    SoundBuffer capture;

    Sound sound;

    public:
    Board();
    void draw_white(RenderTarget& window, char position[8][8], int possible[8][8], int selected_x, int selected_y);
    void draw_black(RenderTarget& window, char position[8][8], int possible[8][8], int selected_x, int selected_y);
    void play_sound(bool capture);
};
