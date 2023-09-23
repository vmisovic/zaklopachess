#include <SFML/Graphics.hpp>
#include "../lib/board.hpp"
#include "../lib/king.hpp"
#include "../lib/queen.hpp"
#include "../lib/rook.hpp"
#include "../lib/bishop.hpp"
#include "../lib/knight.hpp"
#include "../lib/pawn.hpp"

struct Game {
    char position[8][8];
    bool possible[8][8];

    Board board;
    King king;
    Queen queen;
    Rook rook;
    Bishop bishop;
    Knight knight;
    Pawn pawn;

    sf::CircleShape circle;

    void reset_game();
    void reset_possible();

    void draw_possible(sf::RenderTarget& window, int x, int y);

    public:
    Game();
    void move();
    void draw(sf::RenderTarget& window);
};
