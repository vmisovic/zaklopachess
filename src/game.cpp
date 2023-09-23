#include "../lib/game.hpp"
#include <SFML/Graphics/CircleShape.hpp>

Game::Game() {
    circle.setRadius(32.f);
    circle.setFillColor(sf::Color::Red);

    reset_game();
    reset_possible();

    possible[4][4] = true;
}

void Game::reset_game() {
    position[0][0] = 'r';
    position[0][7] = 'r';
    position[0][1] = 'n';
    position[0][6] = 'n';
    position[0][2] = 'b';
    position[0][5] = 'b';
    position[0][3] = 'q';
    position[0][4] = 'k';

    position[7][0] = 'R';
    position[7][7] = 'R';
    position[7][1] = 'N';
    position[7][6] = 'N';
    position[7][2] = 'B';
    position[7][5] = 'B';
    position[7][3] = 'Q';
    position[7][4] = 'K';
    for (int i = 0; i < 8; i++) {
        position[1][i] = 'p';
        position[6][i] = 'P';
    }
    for(int i = 2; i < 6; i++) {
        for(int j = 0; j < 8; j++) {
            position[i][j] = ' ';
        }
    }
}

void Game::reset_possible() {
    for (int i = 0; i < 8; i++){
        for (int j = 0; i < 8; i++){
            possible[i][j] = false;
        }
    }
}

void Game::draw_possible(sf::RenderTarget& window, int x, int y){
    circle.setPosition(sf::Vector2f( 128.f * x + 32.f, 128.f * y + 32.f));
    window.draw(circle);
}


void Game::draw(sf::RenderTarget& window){
    board.draw(window);
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            switch ( position[i][j] ) {
                case 'K':
                    king.draw(window, true, j + 65, 8 - i);
                    break;
                case 'Q':
                    queen.draw(window, true, j + 65, 8 - i);
                    break;
                case 'R':
                    rook.draw(window, true, j + 65, 8 - i);
                    break;
                case 'B':
                    bishop.draw(window, true, j + 65, 8 - i);
                    break;
                case 'N':
                    knight.draw(window, true, j + 65, 8 - i);
                    break;
                case 'P':
                    pawn.draw(window, true, j + 65, 8 - i);
                    break;
                case 'k':
                    king.draw(window, false, j + 65, 8 - i);
                    break;
                case 'q':
                    queen.draw(window, false, j + 65, 8 - i);
                    break;
                case 'r':
                    rook.draw(window, false, j + 65, 8 - i);
                    break;
                case 'b':
                    bishop.draw(window, false, j + 65, 8 - i);
                    break;
                case 'n':
                    knight.draw(window, false, j + 65, 8 - i);
                    break;
                case 'p':
                    pawn.draw(window, false, j + 65, 8 - i);
                    break;
            }

            if(possible[i][j])
                draw_possible(window, i, j);
        }
    }
};
