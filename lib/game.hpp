#include <SFML/Graphics.hpp>
#include <cstring>
#include "../lib/board.hpp"
#include "../lib/ui.hpp"

struct Game {
    private:
    char position[8][8];
    int possible[8][8];

    Board board;
    Ui ui;

    bool turn;
    bool playing;
    bool paused;
    bool rotation;
    bool sound;
    bool perspective;
    bool oo_white;
    bool ooo_white;
    bool oo_black;
    bool ooo_black;
    int enpassant;
    int x;
    int y;

    void new_game();
    void reset_possible();
    void update_enpassant(int x1, int y1);
    void promotion(int x1, int y1);
    void update_castle(int x1, int y1);
    void check_check();
    bool check(int x1, int y1);

    void calc_pawn(bool ch);
    void calc_knight(bool ch);
    void calc_bishop(bool ch);
    void calc_rook(bool ch);
    void calc_queen(bool ch);
    void calc_king(bool ch);

    public:
    Game();
    void show_menu();
    void move(int x, int y);
    void draw(sf::RenderTarget& window);
};
