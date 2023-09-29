#include "../lib/game.hpp"

Game::Game() {
    x = -1;
    y = -1;
    reset_possible();
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j ++)
            position[i][j] = ' ';
    ui.update_settings(&paused, &rotation, &sound, &perspective);
}

void Game::new_game() {
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

    reset_possible();

    x = -1;
    y = -1;
    enpassant = -1;
    oo_white = true;
    ooo_white = true;
    oo_black = true;
    ooo_black = true;
    turn = true;
}

void Game::reset_possible() {
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++)
            possible[i][j] = 0;
}

void Game::draw(sf::RenderTarget& window) {
    window.clear(Color(0x1A1B26FF));
    bool side = (turn && rotation) || (!rotation && perspective);
    board.draw(window, position, possible, x, y, side);
    ui.draw(window, side);
}

void Game::menu() {
    paused = true;
    ui.show_menu();
}

void Game::move(int mouse_x, int mouse_y) {
    int x1 = (mouse_x - 50) / 100;
    int y1 = (mouse_y - 50) / 100;
    if(x1 >= 0 && x1 < 8 && y1 >= 0 && y1 < 8 && !paused) {
        if((!turn && rotation) || (!rotation && !perspective)) {
            x1 = 7 - x1;
            y1 = 7 - y1;
        }
        if(x == -1 || y == -1) {
            if((turn && isupper(position[x1][y1])) || (!turn && islower(position[x1][y1]))) {
                x = x1;
                y = y1;
                pawn(true);
                knight(true);
                bishop(true);
                rook(true);
                queen(true);
                king(true);
            }
        }
        else {
            if(possible[x1][y1]) {
                update_enpassant(x1, y1);
                castle(x1, y1);
                board.play_sound(position[x1][y1] != ' ', sound);
                position[x1][y1] = position[x][y];
                position[x][y] = ' ';
                promotion(x1, y1);
                turn = !turn;
                mate();
            }
            x = -1;
            y = -1;
            reset_possible();
        }
    }
    else {
        ui.input(mouse_y, mouse_x);
        ui.update_settings(&paused, &rotation, &sound, &perspective);
        if(ui.start_game())
            new_game();
    }
}

void Game::pawn(bool ch) {
    if(position[x][y] == 'P') {
        if(!isalpha(position[x - 1][y])) {
            if(ch && !check(x - 1, y))
                possible[x - 1][y] = 1;
            if(x == 6 && !isalpha(position[x - 2][y]) && ch && !check(x - 2, y))
                possible[x - 2][y] = 3;
        }

        if(y > 0 && x == 3 && enpassant == y - 1 && ch && !check(x - 1, y - 1))
            possible[x - 1][y - 1] = 2;
        if(y < 7 && x == 3 && enpassant == y + 1 && ch && !check(x - 1, y + 1))
            possible[x - 1][y + 1] = 2;

        if(y > 0 && islower(position[x - 1][y - 1]))
            if((ch && !check(x - 1, y - 1)) || !ch)
                possible[x - 1][y - 1] = 1;
        if(y < 7 && islower(position[x - 1][y + 1]))
            if((ch && !check(x - 1, y + 1)) || !ch)
                possible[x - 1][y + 1] = 1;
    }
    else if(position[x][y] == 'p') {
        if(!isalpha(position[x + 1][y])) {
            if(ch && !check(x + 1, y))
                possible[x + 1][y] = 1;
            if(x == 1 && !isalpha(position[x + 2][y]) && ch && !check(x + 2, y))
                possible[x + 2][y] = 3;
        }

        if(y > 0 && x == 4 && enpassant == y - 1 && ch && !check(x + 1, y - 1))
            possible[x + 1][y - 1] = 2;
        if(y < 7 && x == 4 && enpassant == y + 1 && ch && !check(x + 1, y + 1))
            possible[x + 1][y + 1] = 2;

        if(y > 0 && isupper(position[x + 1][y - 1]))
            if((ch && !check(x + 1, y - 1)) || !ch)
                possible[x + 1][y - 1] = 1;
        if(y < 7 && isupper(position[x + 1][y + 1]))
            if((ch && !check(x + 1, y + 1)) || !ch)
                possible[x + 1][y + 1] = 1;
    }
}

void Game::promotion(int x1, int y1) {
    if(x1 == 0 && position[x1][y1] == 'P')
        position[x1][y1] = 'Q';
    if(x1 == 7 && position[x1][y1] == 'p')
        position[x1][y1] = 'q';
}

void Game::update_enpassant(int x1, int y1) {
    if(possible[x1][y1] == 3)
        enpassant = y1;
    else
        enpassant = -1;
    if(possible[x1][y1] == 2){
        if(position[x][y] == 'P')
            position[x1 + 1][y1] = ' ';
        else if(position[x][y] == 'p')
            position[x1 - 1][y1] = ' ';
    }
}

void Game::knight(bool ch) {
    if(position[x][y] == 'N') {
        if(x < 6 && y < 7 && !isupper(position[x + 2][y + 1]))
            if((ch && !check(x + 2, y + 1)) || !ch)
                possible[x + 2][y + 1] = 1;
        if(x < 6 && y > 0 && !isupper(position[x + 2][y - 1]))
            if((ch && !check(x + 2, y - 1)) || !ch)
                possible[x + 2][y - 1] = 1;
        if(x > 1 && y < 7 && !isupper(position[x - 2][y + 1]))
            if((ch && !check(x - 2, y + 1)) || !ch)
                possible[x - 2][y + 1] = 1;
        if(x > 1 && y > 0 && !isupper(position[x - 2][y - 1]))
            if((ch && !check(x - 2, y - 1)) || !ch)
                possible[x - 2][y - 1] = 1;
        if(x < 7 && y < 6 && !isupper(position[x + 1][y + 2]))
            if((ch && !check(x + 1, y + 2)) || !ch)
                possible[x + 1][y + 2] = 1;
        if(x < 7 && y > 1 && !isupper(position[x + 1][y - 2]))
            if((ch && !check(x + 1, y - 2)) || !ch)
                possible[x + 1][y - 2] = 1;
        if(x > 0 && y < 6 && !isupper(position[x - 1][y + 2]))
            if((ch && !check(x - 1, y + 2)) || !ch)
                possible[x - 1][y + 2] = 1;
        if(x > 0 && y > 1 && !isupper(position[x - 1][y - 2]))
            if((ch && !check(x - 1, y - 2)) || !ch)
                possible[x - 1][y - 2] = 1;
    }
    else if(position[x][y] == 'n') {
        if(x < 6 && y < 7 && !islower(position[x + 2][y + 1]))
            if((ch && !check(x + 2, y + 1)) || !ch)
                possible[x + 2][y + 1] = 1;
        if(x < 6 && y > 0 && !islower(position[x + 2][y - 1]))
            if((ch && !check(x + 2, y - 1)) || !ch)
                possible[x + 2][y - 1] = 1;
        if(x > 1 && y < 7 && !islower(position[x - 2][y + 1]))
            if((ch && !check(x - 2, y + 1)) || !ch)
                possible[x - 2][y + 1] = 1;
        if(x > 1 && y > 0 && !islower(position[x - 2][y - 1]))
            if((ch && !check(x - 2, y - 1)) || !ch)
                possible[x - 2][y - 1] = 1;
        if(x < 7 && y < 6 && !islower(position[x + 1][y + 2]))
            if((ch && !check(x + 1, y + 2)) || !ch)
                possible[x + 1][y + 2] = 1;
        if(x < 7 && y > 1 && !islower(position[x + 1][y - 2]))
            if((ch && !check(x + 1, y - 2)) || !ch)
                possible[x + 1][y - 2] = 1;
        if(x > 0 && y < 6 && !islower(position[x - 1][y + 2]))
            if((ch && !check(x - 1, y + 2)) || !ch)
                possible[x - 1][y + 2] = 1;
        if(x > 0 && y > 1 && !islower(position[x - 1][y - 2]))
            if((ch && !check(x - 1, y - 2)) || !ch)
                possible[x - 1][y - 2] = 1;
    }
}

void Game::bishop(bool ch) {
    if(position[x][y] == 'b' || position[x][y] == 'B') {
        // down right
        for(int i = 1; x + i < 8 && y + i < 8; i++) {
            if(position[x + i][y + i] == ' ') {
                if((ch && !check(x + i, y + i)) || !ch)
                    possible[x + i][y + i] = 1;
            }
            else if((position[x][y] == 'B' && islower(position[x + i][y + i])) || 
                    (position[x][y] == 'b' && isupper(position[x + i][y + i]))) {
                if((ch && !check(x + i, y + i)) || !ch)
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
            if(position[x + i][y - i] == ' ') {
                if((ch && !check(x + i, y - i)) || !ch)
                    possible[x + i][y - i] = 1;
            }
            else if((position[x][y] == 'B' && islower(position[x + i][y - i])) || 
                    (position[x][y] == 'b' && isupper(position[x + i][y - i]))) {
                if((ch && !check(x + i, y - i)) || !ch)
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
            if(position[x - i][y + i] == ' ') {
                if((ch && !check(x - i, y + i)) || !ch)
                    possible[x - i][y + i] = 1;
            }
            else if((position[x][y] == 'B' && islower(position[x - i][y + i])) || 
                    (position[x][y] == 'b' && isupper(position[x - i][y + i]))) {
                if((ch && !check(x - i, y + i)) || !ch)
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
            if(position[x - i][y - i] == ' ') {
                if((ch && !check(x - i, y - i)) || !ch)
                    possible[x - i][y - i] = 1;
            }
            else if((position[x][y] == 'B' && islower(position[x - i][y - i])) || 
                    (position[x][y] == 'b' && isupper(position[x - i][y - i]))) {
                if((ch && !check(x - i, y - i)) || !ch)
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

void Game::rook(bool ch) {
    if(position[x][y] == 'r' || position[x][y] == 'R') {
        // down
        for(int i = 1; x + i < 8; i++) {
            if(position[x + i][y] == ' ') {
                if((ch && !check(x + i, y)) || !ch)
                    possible[x + i][y] = 1;
            }
            else if((position[x][y] == 'R' && islower(position[x + i][y])) || 
                    (position[x][y] == 'r' && isupper(position[x + i][y]))) {
                if((ch && !check(x + i, y)) || !ch)
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
            if(position[x - i][y] == ' ') {
                if((ch && !check(x - i, y)) || !ch)
                    possible[x - i][y] = 1;
            }
            else if((position[x][y] == 'R' && islower(position[x - i][y])) || 
                    (position[x][y] == 'r' && isupper(position[x - i][y]))) {
                if((ch && !check(x - i, y)) || !ch)
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
            if(position[x][y + i] == ' ') {
                if((ch && !check(x, y + i)) || !ch)
                    possible[x][y + i] = 1;
            }
            else if((position[x][y] == 'R' && islower(position[x][y + i])) || 
                    (position[x][y] == 'r' && isupper(position[x][y + i]))) {
                if((ch && !check(x, y + i)) || !ch)
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
            if(position[x][y - i] == ' ') {
                if((ch && !check(x, y - i)) || !ch)
                    possible[x][y - i] = 1;
            }
            else if((position[x][y] == 'R' && islower(position[x][y - i])) || 
                    (position[x][y] == 'r' && isupper(position[x][y - i]))) {
                if((ch && !check(x, y - i)) || !ch)
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

void Game::queen(bool ch) {
    if(position[x][y] == 'q' || position[x][y] == 'Q') {
        // down
        for(int i = 1; x + i < 8; i++) {
            if(position[x + i][y] == ' ') {
                if((ch && !check(x + i, y)) || !ch)
                    possible[x + i][y] = 1;
            }
            else if((position[x][y] == 'Q' && islower(position[x + i][y])) || 
                    (position[x][y] == 'q' && isupper(position[x + i][y]))) {
                if((ch && !check(x + i, y)) || !ch)
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
            if(position[x - i][y] == ' ') {
                if((ch && !check(x - i, y)) || !ch)
                    possible[x - i][y] = 1;
            }
            else if((position[x][y] == 'Q' && islower(position[x - i][y])) || 
                    (position[x][y] == 'q' && isupper(position[x - i][y]))) {
                if((ch && !check(x - i, y)) || !ch)
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
            if(position[x][y + i] == ' ') {
                if((ch && !check(x, y + i)) || !ch)
                    possible[x][y + i] = 1;
            }
            else if((position[x][y] == 'Q' && islower(position[x][y + i])) || 
                    (position[x][y] == 'q' && isupper(position[x][y + i]))) {
                if((ch && !check(x, y + i)) || !ch)
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
            if(position[x][y - i] == ' ') {
                if((ch && !check(x, y - i)) || !ch)
                    possible[x][y - i] = 1;
            }
            else if((position[x][y] == 'Q' && islower(position[x][y - i])) || 
                    (position[x][y] == 'q' && isupper(position[x][y - i]))) {
                if((ch && !check(x, y - i)) || !ch)
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
            if(position[x + i][y + i] == ' ') {
                if((ch && !check(x + i, y + i)) || !ch)
                    possible[x + i][y + i] = 1;
            }
            else if((position[x][y] == 'Q' && islower(position[x + i][y + i])) || 
                    (position[x][y] == 'q' && isupper(position[x + i][y + i]))) {
                if((ch && !check(x + i, y + i)) || !ch)
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
            if(position[x + i][y - i] == ' ') {
                if((ch && !check(x + i, y - i)) || !ch)
                    possible[x + i][y - i] = 1;
            }
            else if((position[x][y] == 'Q' && islower(position[x + i][y - i])) || 
                    (position[x][y] == 'q' && isupper(position[x + i][y - i]))) {
                if((ch && !check(x + i, y - i)) || !ch)
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
            if(position[x - i][y + i] == ' ') {
                if((ch && !check(x - i, y + i)) || !ch)
                    possible[x - i][y + i] = 1;
            }
            else if((position[x][y] == 'Q' && islower(position[x - i][y + i])) ||
                    (position[x][y] == 'q' && isupper(position[x - i][y + i]))) {
                if((ch && !check(x - i, y + i)) || !ch)
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
            if(position[x - i][y - i] == ' ') {
                if((ch && !check(x - i, y - i)) || !ch)
                    possible[x - i][y - i] = 1;
            }
            else if((position[x][y] == 'Q' && islower(position[x - i][y - i])) || 
                    (position[x][y] == 'q' && isupper(position[x - i][y - i]))) {
                if((ch && !check(x - i, y - i)) || !ch)
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

void Game::king(bool ch) {
    if(position[x][y] == 'k' || position[x][y] == 'K') {
        // down
        if(x < 7) {
            if(position[x + 1][y] == ' ' ||
                    (position[x][y] == 'K' && islower(position[x + 1][y])) ||
                    (position[x][y] == 'k' && isupper(position[x + 1][y])))
                if((ch && !check(x + 1, y)) || !ch)
                    possible[x + 1][y] = 1;
        }
        // up
        if(x > 0) {
            if(position[x - 1][y] == ' ' ||
                    (position[x][y] == 'K' && islower(position[x - 1][y])) ||
                    (position[x][y] == 'k' && isupper(position[x - 1][y])))
                if((ch && !check(x - 1, y)) || !ch)
                    possible[x - 1][y] = 1;
        }
        // right
        if(y < 7) {
            if( position[x][y + 1] == ' ' ||
                    (position[x][y] == 'K' && islower(position[x][y + 1])) ||
                    (position[x][y] == 'k' && isupper(position[x][y + 1]))) {
                if((ch && !check(x, y + 1)) || !ch)
                    possible[x][y + 1] = 1;
            }
        }
        // left
        if(y > 0) {
            if(position[x][y - 1] == ' ' ||
                    (position[x][y] == 'K' && islower(position[x][y - 1])) ||
                    (position[x][y] == 'k' && isupper(position[x][y - 1])))
                if((ch && !check(x, y - 1)) || !ch)
                    possible[x][y - 1] = 1;
        }
        // down right
        if(x < 7 && y < 7) {
            if((position[x + 1][y + 1] == ' ') ||
                    (position[x][y] == 'K' && islower(position[x + 1][y + 1])) ||
                    (position[x][y] == 'k' && isupper(position[x + 1][y + 1])))
                if((ch && !check(x + 1, y + 1)) || !ch)
                    possible[x + 1][y + 1] = 1;
        }
        // down left
        if(x < 7 && y > 0) {
            if(position[x + 1][y - 1] == ' ' ||
                    (position[x][y] == 'K' && islower(position[x + 1][y - 1])) ||
                    (position[x][y] == 'k' && isupper(position[x + 1][y - 1])))
                if((ch && !check(x + 1, y - 1)) || !ch)
                    possible[x + 1][y - 1] = 1;
        }
        // up right
        if(x > 0 && y < 7) {
            if(position[x - 1][y + 1] == ' ' ||
                    (position[x][y] == 'K' && islower(position[x - 1][y + 1])) ||
                    (position[x][y] == 'k' && isupper(position[x - 1][y + 1])))
                if((ch && !check(x - 1, y + 1)) || !ch)
                    possible[x - 1][y + 1] = 1;
        }
        // up left
        if(x > 0 && y > 0) {
            if(position[x - 1][y - 1] == ' ' ||
                    (position[x][y] == 'K' && islower(position[x - 1][y - 1])) ||
                    (position[x][y] == 'k' && isupper(position[x - 1][y - 1])))
                if((ch && !check(x - 1, y - 1)) || !ch)
                    possible[x - 1][y - 1] = 1;
        }
        // castle
        if(y == 4) {
            if(position[x][y] == 'K' && position[7][5] == ' ' && position[7][6] == ' ' && oo_white)
                if(ch && !check(7, 6) && !check(7, 5) && !check(7, 4))
                    possible[7][6] = 4;
            if(position[x][y] == 'K' && position[7][3] == ' ' && position[7][2] == ' ' && position[7][1] == ' ' && ooo_white)
                if(ch && !check(7, 2) && !check(7, 3) && !check(7, 4))
                    possible[7][2] = 5;
            if(position[x][y] == 'k' && position[0][5] == ' ' && position[0][6] == ' ' && oo_black)
                if(ch && !check(0, 6) && !check(0, 5) && !check(0, 4))
                    possible[0][6] = 6;
            if(position[x][y] == 'k' && position[0][3] == ' ' && position[0][2] == ' ' && position[0][1] && ooo_black)
                if(ch && !check(0, 2) && !check(0, 3) && !check(0, 4))
                    possible[0][2] = 7;
        }
    }
}

void Game::castle(int x1, int y1) {
    if(position[7][7] != 'R')
        oo_white = false;
    if(position[7][0] != 'R')
        ooo_white = false;
    if(position[7][4] != 'K') {
        oo_white = false;
        ooo_white = false;
    }
    if(position[0][7] != 'r')
        oo_black = false;
    if(position[0][0] != 'r')
        ooo_black = false;
    if(position[0][4] != 'k') {
        oo_black = false;
        ooo_black = false;
    }

    if(possible[x1][y1] == 4) {
        position[7][5] = position[7][7];
        position[7][7] = ' ';
    }
    if(possible[x1][y1] == 5) {
        position[7][3] = position[7][0];
        position[7][0] = ' ';
    }
    if(possible[x1][y1] == 6) {
        position[0][5] = position[0][7];
        position[0][7] = ' ';
    }
    if(possible[x1][y1] == 7) {
        position[0][3] = position[0][0];
        position[0][0] = ' ';
    }
}

bool Game::check(int x1, int y1) {
    int tmp_x = x;
    int tmp_y = y;
    char tmp_piece = position[x1][y1];
    position[x1][y1] = position[x][y];
    position[x][y] = ' ';

    int tmp_possible[8][8];
    std::memcpy(tmp_possible, possible, 64 * sizeof(int));

    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if((turn && islower(position[i][j])) || (!turn && isupper(position[i][j]))) {
                x = i;
                y = j;
                reset_possible();
                pawn(false);
                knight(false);
                bishop(false);
                rook(false);
                queen(false);
                king(false);
                for(int m = 0; m < 8; m++) {
                    for (int n = 0; n < 8; n++) {
                        if(possible[m][n] && ((turn && position[m][n] == 'K') || (!turn && position[m][n] == 'k'))) {
                            x = tmp_x;
                            y = tmp_y;
                            position[x][y] = position[x1][y1];
                            position[x1][y1] = tmp_piece;
                            std::memcpy(possible, tmp_possible, 64 * sizeof(int));
                            return true;
                        }
                    }
                }
            }
        }
    }
    x = tmp_x;
    y = tmp_y;
    position[x][y] = position[x1][y1];
    position[x1][y1] = tmp_piece;
    std::memcpy(possible, tmp_possible, 64 * sizeof(int));
    return false;
}

bool Game::end() {
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if((turn && isupper(position[i][j])) || (!turn && islower(position[i][j]))) {
                x = i;
                y = j;
                reset_possible();
                pawn(true);
                knight(true);
                bishop(true);
                rook(true);
                queen(true);
                king(true);
                for(int m = 0; m < 8; m++) {
                    for (int n = 0; n < 8; n++) {
                        if(possible[m][n]) {
                            return false;
                        }
                    }
                }
            }
        }
    }
    return true;
}

void Game::mate() {
    if(end()) {
        ui.end_game(check(-1, -1), turn);
    }
}
