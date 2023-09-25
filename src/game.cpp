#include "../lib/game.hpp"

Game::Game() {
    turn = true;
    enpassant = -1;
    selected_x = -1;
    selected_y = -1;

    reset_game();
    reset_possible();
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

    for(int i = 0; i < 8; i++) {
        position[1][i] = 'p';
        position[6][i] = 'P';
    }

    for(int i = 2; i < 6; i++)
        for(int j = 0; j < 8; j++)
            position[i][j] = ' ';
}

void Game::reset_possible() {
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++)
            possible[i][j] = 0;
}

void Game::draw(sf::RenderTarget& window) {
    board.draw(window, position, possible, selected_x, selected_y);
}

void Game::move(int x, int y){
    if(x >= 0 && x < 8 && y >= 0 && y < 8) {
        if(selected_x == -1 || selected_y == -1) {
            if((turn && isupper(position[x][y])) || (!turn && islower(position[x][y]))) {
                selected_x = x;
                selected_y = y;
                calc_moves();
            }
        }
        else {
            if(possible[x][y]) {
                update_enpassant(x, y);
                position[x][y] = position[selected_x][selected_y];
                position[selected_x][selected_y] = ' ';
                promotion(x, y);
                turn = !turn;
            }
            selected_x = -1;
            selected_y = -1;
            reset_possible();
        }
    }
}

void Game::calc_moves() {
    calc_pawn();
    calc_knight();
    calc_bishop();
    calc_rook();
    calc_queen();
    calc_king();
}

void Game::calc_pawn() {
    int x = selected_x;
    int y = selected_y;
    if(position[x][y] == 'P') {
        if(!isalpha(position[x - 1][y])) {
            possible[x - 1][y] = 1;
            if(x == 6 && !isalpha(position[x - 2][y])) {
                possible[x - 2][y] = 3;
            }
        }

        if(y > 0 && x == 3 && enpassant == y - 1)
            possible[x - 1][y - 1] = 2;
        if(y < 7 && x == 3 && enpassant == y + 1)
            possible[x - 1][y + 1] = 2;

        if(y > 0 && islower(position[x - 1][y - 1]))
            possible[x - 1][y - 1] = 1;
        if(y < 7 && islower(position[x - 1][y + 1]))
            possible[x - 1][y + 1] = 1;
    }
    else if(position[x][y] == 'p') {
        if(!isalpha(position[x + 1][y])) {
            possible[x + 1][y] = 1;
            possible[x + 1][y] = 1;
            if(x == 1 && !isalpha(position[x + 2][y])) {
                possible[x + 2][y] = 3;
            }
        }

        if(y > 0 && x == 4 && enpassant == y - 1)
            possible[x + 1][y - 1] = 2;
        if(y < 7 && x == 4 && enpassant == y + 1)
            possible[x + 1][y + 1] = 2;

        if(y > 0 && isupper(position[x + 1][y - 1]))
            possible[x + 1][y - 1] = 1;
        if(y < 7 && isupper(position[x + 1][y + 1]))
            possible[x + 1][y + 1] = 1;
    }
}

void Game::promotion(int x, int y) {
    if(x == 0 && position[x][y] == 'P')
        position[x][y] = 'Q';
    if(x == 7 && position[x][y] == 'p')
        position[x][y] = 'q';
}

void Game::update_enpassant(int x, int y) {
    if(possible[x][y] == 3)
        enpassant = y;
    else
        enpassant = -1;
    if(possible[x][y] == 2){
        if(position[selected_x][selected_y] == 'P')
            position[x + 1][y] = ' ';
        else if(position[selected_x][selected_y] == 'p')
            position[x - 1][y] = ' ';
    }
}

void Game::calc_knight() {
    int x = selected_x;
    int y = selected_y;

    if(position[x][y] == 'N') {
        if(x < 6 && y < 7 && !isupper(position[x + 2][y + 1]))
            possible[x + 2][y + 1] = 1;
        if(x < 6 && y > 0 && !isupper(position[x + 2][y - 1]))
            possible[x + 2][y - 1] = 1;
        if(x > 1 && y < 7 && !isupper(position[x - 2][y + 1]))
            possible[x - 2][y + 1] = 1;
        if(x > 1 && y > 0 && !isupper(position[x - 2][y - 1]))
            possible[x - 2][y - 1] = 1;
        if(x < 7 && y < 6 && !isupper(position[x + 1][y + 2]))
            possible[x + 1][y + 2] = 1;
        if(x < 7 && y > 1 && !isupper(position[x + 1][y - 2]))
            possible[x + 1][y - 2] = 1;
        if(x > 0 && y < 6 && !isupper(position[x - 1][y + 2]))
            possible[x - 1][y + 2] = 1;
        if(x > 0 && y > 1 && !isupper(position[x - 1][y - 2]))
            possible[x - 1][y - 2] = 1;
    }
    else if(position[x][y] == 'n') {
        if(x < 6 && y < 7 && !islower(position[x + 2][y + 1]))
            possible[x + 2][y + 1] = 1;
        if(x < 6 && y > 0 && !islower(position[x + 2][y - 1]))
            possible[x + 2][y - 1] = 1;
        if(x > 1 && y < 7 && !islower(position[x - 2][y + 1]))
            possible[x - 2][y + 1] = 1;
        if(x > 1 && y > 0 && !islower(position[x - 2][y - 1]))
            possible[x - 2][y - 1] = 1;
        if(x < 7 && y < 6 && !islower(position[x + 1][y + 2]))
            possible[x + 1][y + 2] = 1;
        if(x < 7 && y > 1 && !islower(position[x + 1][y - 2]))
            possible[x + 1][y - 2] = 1;
        if(x > 0 && y < 6 && !islower(position[x - 1][y + 2]))
            possible[x - 1][y + 2] = 1;
        if(x > 0 && y > 1 && !islower(position[x - 1][y - 2]))
            possible[x - 1][y - 2] = 1;
    }
}

void Game::calc_bishop() {
    int x = selected_x;
    int y = selected_y;
    // down right
    if(position[x][y] == 'b' || position[x][y] == 'B') {
        for(int i = 1; x + i < 8 && y + i < 8; i++) {
            if(position[x + i][y + i] == ' ')
                possible[x + i][y + i] = 1;
            else if((position[x][y] == 'B' && islower(position[x + i][y + i])) || 
                    (position[x][y] == 'b' && isupper(position[x + i][y + i]))) {
                possible[x + i][y + i] = 1;
                break;
            }
            else if((position[x][y] == 'B' && isupper(position[x + i][y + i])) || 
                    (position[x][y] == 'b' && islower(position[x + i][y + i]))) {
                break;
            }
        }
        // down left
        for(int i = 1; x + i < 8 && y - i >= 0; i++) {
            if(position[x + i][y - i] == ' ')
                possible[x + i][y - i] = 1;
            else if((position[x][y] == 'B' && islower(position[x + i][y - i])) || 
                    (position[x][y] == 'b' && isupper(position[x + i][y - i]))) {
                possible[x + i][y - i] = 1;
                break;
            }
            else if((position[x][y] == 'B' && isupper(position[x + i][y - i])) || 
                    (position[x][y] == 'b' && islower(position[x + i][y - i]))) {
                break;
            }
        }
        // up right
        for(int i = 1; x - i >= 0 && y + i < 8; i++) {
            if(position[x - i][y + i] == ' ')
                possible[x - i][y + i] = 1;
            else if((position[x][y] == 'B' && islower(position[x - i][y + i])) || 
                    (position[x][y] == 'b' && isupper(position[x - i][y + i]))) {
                possible[x - i][y + i] = 1;
                break;
            }
            else if((position[x][y] == 'B' && isupper(position[x - i][y + i])) || 
                    (position[x][y] == 'b' && islower(position[x - i][y + i]))) {
                break;
            }
        }
        // up left
        for(int i = 1; x - i >= 0 && y - i >= 0; i++) {
            if(position[x - i][y - i] == ' ')
                possible[x - i][y - i] = 1;
            else if((position[x][y] == 'B' && islower(position[x - i][y - i])) || 
                    (position[x][y] == 'b' && isupper(position[x - i][y - i]))) {
                possible[x - i][y - i] = 1;
                break;
            }
            else if((position[x][y] == 'B' && isupper(position[x - i][y - i])) || 
                    (position[x][y] == 'b' && islower(position[x - i][y - i]))) {
                break;
            }
        }
    }
}

void Game::calc_rook() {
    int x = selected_x;
    int y = selected_y;

    if(position[x][y] == 'r' || position[x][y] == 'R') {
        // down
        for(int i = 1; x + i < 8; i++) {
            if(position[x + i][y] == ' ')
                possible[x + i][y] = 1;
            else if((position[x][y] == 'R' && islower(position[x + i][y])) || 
                    (position[x][y] == 'r' && isupper(position[x + i][y]))) {
                possible[x + i][y] = 1;
                break;
            }
            else if((position[x][y] == 'R' && isupper(position[x + i][y])) || 
                    (position[x][y] == 'r' && islower(position[x + i][y]))) {
                break;
            }
        }
        // up
        for(int i = 1; x - i >= 0; i++) {
            if(position[x - i][y] == ' ')
                possible[x - i][y] = 1;
            else if((position[x][y] == 'R' && islower(position[x - i][y])) || 
                    (position[x][y] == 'r' && isupper(position[x - i][y]))) {
                possible[x - i][y] = 1;
                break;
            }
            else if((position[x][y] == 'R' && isupper(position[x - i][y])) || 
                    (position[x][y] == 'r' && islower(position[x - i][y]))) {
                break;
            }
        }
        // right
        for(int i = 1; y + i < 8; i++) {
            if(position[x][y + i] == ' ')
                possible[x][y + i] = 1;
            else if((position[x][y] == 'R' && islower(position[x][y + i])) || 
                    (position[x][y] == 'r' && isupper(position[x][y + i]))) {
                possible[x][y + i] = 1;
                break;
            }
            else if((position[x][y] == 'R' && isupper(position[x][y + i])) || 
                    (position[x][y] == 'r' && islower(position[x][y + i]))) {
                break;
            }
        }
        // left
        for(int i = 1; y - i >= 0; i++) {
            if(position[x][y - i] == ' ')
                possible[x][y - i] = 1;
            else if((position[x][y] == 'R' && islower(position[x][y - i])) || 
                    (position[x][y] == 'r' && isupper(position[x][y - i]))) {
                possible[x][y - i] = 1;
                break;
            }
            else if((position[x][y] == 'R' && isupper(position[x][y - i])) || 
                    (position[x][y] == 'r' && islower(position[x][y - i]))) {
                break;
            }
        }
    }
}

void Game::calc_queen() {
    int x = selected_x;
    int y = selected_y;

    if(position[x][y] == 'q' || position[x][y] == 'Q') {
        // down
        for(int i = 1; x + i < 8; i++) {
            if(position[x + i][y] == ' ')
                possible[x + i][y] = 1;
            else if((position[x][y] == 'Q' && islower(position[x + i][y])) || 
                    (position[x][y] == 'q' && isupper(position[x + i][y]))) {
                possible[x + i][y] = 1;
                break;
            }
            else if((position[x][y] == 'Q' && isupper(position[x + i][y])) || 
                    (position[x][y] == 'q' && islower(position[x + i][y]))) {
                break;
            }
        }
        // up
        for(int i = 1; x - i >= 0; i++) {
            if(position[x - i][y] == ' ')
                possible[x - i][y] = 1;
            else if((position[x][y] == 'Q' && islower(position[x - i][y])) || 
                    (position[x][y] == 'q' && isupper(position[x - i][y]))) {
                possible[x - i][y] = 1;
                break;
            }
            else if((position[x][y] == 'Q' && isupper(position[x - i][y])) || 
                    (position[x][y] == 'q' && islower(position[x - i][y]))) {
                break;
            }
        }
        // right
        for(int i = 1; y + i < 8; i++) {
            if(position[x][y + i] == ' ')
                possible[x][y + i] = 1;
            else if((position[x][y] == 'Q' && islower(position[x][y + i])) || 
                    (position[x][y] == 'q' && isupper(position[x][y + i]))) {
                possible[x][y + i] = 1;
                break;
            }
            else if((position[x][y] == 'Q' && isupper(position[x][y + i])) || 
                    (position[x][y] == 'q' && islower(position[x][y + i]))) {
                break;
            }
        }
        // left
        for(int i = 1; y - i >= 0; i++) {
            if(position[x][y - i] == ' ')
                possible[x][y - i] = 1;
            else if((position[x][y] == 'Q' && islower(position[x][y - i])) || 
                    (position[x][y] == 'q' && isupper(position[x][y - i]))) {
                possible[x][y - i] = 1;
                break;
            }
            else if((position[x][y] == 'Q' && isupper(position[x][y - i])) || 
                    (position[x][y] == 'q' && islower(position[x][y - i]))) {
                break;
            }
        }
        // down right
        for(int i = 1; x + i < 8 && y + i < 8; i++) {
            if(position[x + i][y + i] == ' ')
                possible[x + i][y + i] = 1;
            else if((position[x][y] == 'Q' && islower(position[x + i][y + i])) || 
                    (position[x][y] == 'q' && isupper(position[x + i][y + i]))) {
                possible[x + i][y + i] = 1;
                break;
            }
            else if((position[x][y] == 'Q' && isupper(position[x + i][y + i])) || 
                    (position[x][y] == 'q' && islower(position[x + i][y + i]))) {
                break;
            }
        }
        // down left
        for(int i = 1; x + i < 8 && y - i >= 0; i++) {
            if(position[x + i][y - i] == ' ')
                possible[x + i][y - i] = 1;
            else if((position[x][y] == 'Q' && islower(position[x + i][y - i])) || 
                    (position[x][y] == 'q' && isupper(position[x + i][y - i]))) {
                possible[x + i][y - i] = 1;
                break;
            }
            else if((position[x][y] == 'Q' && isupper(position[x + i][y - i])) || 
                    (position[x][y] == 'q' && islower(position[x + i][y - i]))) {
                break;
            }
        }
        // up right
        for(int i = 1; x - i >= 0 && y + i < 8; i++) {
            if(position[x - i][y + i] == ' ')
                possible[x - i][y + i] = 1;
            else if((position[x][y] == 'Q' && islower(position[x - i][y + i])) ||
                    (position[x][y] == 'q' && isupper(position[x - i][y + i]))) {
                possible[x - i][y + i] = 1;
                break;
            }
            else if((position[x][y] == 'Q' && isupper(position[x - i][y + i])) ||
                    (position[x][y] == 'q' && islower(position[x - i][y + i]))) {
                break;
            }
        }
        // up left
        for(int i = 1; x - i >= 0 && y - i >= 0; i++) {
            if(position[x - i][y - i] == ' ')
                possible[x - i][y - i] = 1;
            else if((position[x][y] == 'Q' && islower(position[x - i][y - i])) || 
                    (position[x][y] == 'q' && isupper(position[x - i][y - i]))) {
                possible[x - i][y - i] = 1;
                break;
            }
            else if((position[x][y] == 'Q' && isupper(position[x - i][y - i])) || 
                    (position[x][y] == 'q' && islower(position[x - i][y - i]))) {
                break;
            }
        }
    }
}

void Game::calc_king() {
    int x = selected_x;
    int y = selected_y;
    if(position[x][y] == 'k' || position[x][y] == 'K') {
        // down
        if(x < 7) {
            if(position[x + 1][y] == ' ' ||
                    (position[x][y] == 'K' && islower(position[x + 1][y])) ||
                    (position[x][y] == 'k' && isupper(position[x + 1][y])))
                possible[x + 1][y] = 1;
        }
        // up
        if(x > 0) {
            if(position[x - 1][y] == ' ' ||
                    (position[x][y] == 'K' && islower(position[x - 1][y])) ||
                    (position[x][y] == 'k' && isupper(position[x - 1][y])))
                possible[x - 1][y] = 1;
        }
        // right
        if(y < 7) {
            if( position[x][y + 1] == ' ' ||
                    (position[x][y] == 'K' && islower(position[x][y + 1])) ||
                    (position[x][y] == 'k' && isupper(position[x][y + 1])))
                possible[x][y + 1] = 1;
        }
        // left
        if(y > 0) {
            if(position[x][y - 1] == ' ' ||
                    (position[x][y] == 'K' && islower(position[x][y - 1])) ||
                    (position[x][y] == 'k' && isupper(position[x][y - 1])))
                possible[x][y - 1] = 1;
        }
        // down right
        if(x < 7 && y < 7) {
            if((position[x + 1][y + 1] == ' ') ||
                    (position[x][y] == 'K' && islower(position[x + 1][y + 1])) ||
                    (position[x][y] == 'k' && isupper(position[x + 1][y + 1])))
                possible[x + 1][y + 1] = 1;
        }
        // down left
        if(x < 7 && y > 0) {
            if(position[x + 1][y - 1] == ' ' ||
                    (position[x][y] == 'K' && islower(position[x + 1][y - 1])) ||
                    (position[x][y] == 'k' && isupper(position[x + 1][y - 1])))
                possible[x + 1][y - 1] = 1;
        }
        // up right
        if(x > 0 && y < 7) {
            if(position[x - 1][y + 1] == ' ' ||
                    (position[x][y] == 'K' && islower(position[x - 1][y + 1])) ||
                    (position[x][y] == 'k' && isupper(position[x - 1][y + 1])))
                possible[x - 1][y + 1] = 1;
        }
        // up left
        if(x > 0 && y > 0) {
            if(position[x - 1][y - 1] == ' ' ||
                    (position[x][y] == 'K' && islower(position[x - 1][y - 1])) ||
                    (position[x][y] == 'k' && isupper(position[x - 1][y - 1])))
                possible[x - 1][y - 1] = 1;
        }
    }
}
