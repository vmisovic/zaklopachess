#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <cstring>
#include "ui.hpp"

struct Game {
    private:
    char position[8][8];
    int possible[8][8];

    Ui ui;

    bool turn;
    bool oo_white;
    bool ooo_white;
    bool oo_black;
    bool ooo_black;
    int enpassant;
    int x;
    int y;
    int moves;

    void new_game();
    void reset_possible();
    void update_enpassant(int x1, int y1);
    void promotion(int x1, int y1);
    void castle(int x1, int y1);
    bool check(int x1, int y1);
    bool end();

    void pawn(bool ch);
    void knight(bool ch);
    void bishop(bool ch);
    void rook(bool ch);
    void queen(bool ch);
    void king(bool ch);

    public:
    Game();
    void move(int x, int y);
    void draw(sf::RenderTarget& window);
};

#endif
