#include <SFML/Graphics.hpp>
#include "../lib/board.hpp"

struct Game {
    char position[8][8];
    int possible[8][8];

    Board board;

    bool turn;
    int enpassant;
    int selected_x;
    int selected_y;

    void reset_game();
    void reset_possible();

    void update_enpassant(int x, int y);
    void promotion(int x, int y);

    void calc_moves();
    void calc_pawn();
    void calc_knight();
    void calc_bishop();
    void calc_rook();
    void calc_queen();
    void calc_king();

    public:
    Game();
    void move(int x, int y);
    void draw(sf::RenderTarget& window);
};
