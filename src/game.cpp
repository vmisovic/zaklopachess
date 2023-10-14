#include "game.hpp"

Game::Game() {
    new_game();
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
    moved = false;
    turn = true;
    ch = true;
}

void Game::reset_possible() {
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++)
            possible[i][j] = 0;
}

void Game::play(int x1, int y1) {
    capture = false;
    moved = false;
    if(x == -1 || y == -1) {
        if((turn && isupper(position[x1][y1])) || (!turn && islower(position[x1][y1]))) {
            x = x1;
            y = y1;
            pawn();
            knight();
            bishop();
            rook();
            king();
        }
    }
    else {
        if(possible[x1][y1]) {
            update_enpassant(x1, y1);
            castle(x1, y1);
            if(position[x1][y1] != ' ') capture = true;
            make_move(x1, y1);
            position[x1][y1] = position[x][y];
            position[x][y] = ' ';
            promotion(x1, y1);
            moved = true;
            turn = !turn;
            end();
        }
        x = -1;
        y = -1;
        reset_possible();
    }
}

void Game::make_move(int x1, int y1) {
    move = "";
    if(!turn) move += toupper(position[x][y]);
    else move += position[x][y];
    move += 65 + y;
    move += 56 - x;
    if(capture) move += 'X';
    move += 65 + y1;
    move += 56 - x1;
    cerr << move << endl;
}

void paly_move(string move) {
}

bool Game::check_square(int x1, int y1) {
    if (x1 < 8 && x1 >= 0 && y1 < 8 && y1 >= 0 && (!ch || !check(x1, y1)) &&
            ((!isupper(position[x1][y1]) && (isupper(position[x][y]))) ||
             (!islower(position[x1][y1]) && islower(position[x][y])))) {
        if((!turn && position[x1][y1] == 'k') || (turn && position[x1][y1] == 'K'))
            next_check = true;
        if(ch) mate = 0;
        return true;
    }
    return false;
}

void Game::pawn() {
    if(position[x][y] == 'P') {
        if(!isalpha(position[x - 1][y])) {
            if(check_square(x - 1, y))
                possible[x - 1][y] = 1;
            if(x == 6 && !isalpha(position[x - 2][y]) && check_square(x - 2, y))
                possible[x - 2][y] = 3;
        }
        if(x == 3 && enpassant == y - 1 && check_square(x - 1, y - 1))
            possible[x - 1][y - 1] = 2;
        if(x == 3 && enpassant == y + 1 && check_square(x - 1, y + 1))
            possible[x - 1][y + 1] = 2;
        if(islower(position[x - 1][y - 1]) && check_square(x - 1, y - 1))
            possible[x - 1][y - 1] = 1;
        if(islower(position[x - 1][y + 1]) && check_square(x - 1, y + 1))
            possible[x - 1][y + 1] = 1;
    }
    else if(position[x][y] == 'p') {
        if(!isalpha(position[x + 1][y])) {
            if(check_square(x + 1, y))
                possible[x + 1][y] = 1;
            if(x == 1 && !isalpha(position[x + 2][y]) && check_square(x + 2, y))
                possible[x + 2][y] = 3;
        }
        if(x == 4 && enpassant == y - 1 && check_square(x + 1, y - 1))
            possible[x + 1][y - 1] = 2;
        if(x == 4 && enpassant == y + 1 && check_square(x + 1, y + 1))
            possible[x + 1][y + 1] = 2;
        if(isupper(position[x + 1][y - 1]) && check_square(x + 1, y - 1))
            possible[x + 1][y - 1] = 1;
        if(isupper(position[x + 1][y + 1]) && check_square(x + 1, y + 1))
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
        capture = true;
        if(position[x][y] == 'P')
            position[x1 + 1][y1] = ' ';
        else if(position[x][y] == 'p')
            position[x1 - 1][y1] = ' ';
    }
}

void Game::knight() {
    if(position[x][y] == 'N' || position[x][y] == 'n') {
        if(check_square(x + 2, y + 1))
            possible[x + 2][y + 1] = 1;
        if(check_square(x + 2, y - 1))
            possible[x + 2][y - 1] = 1;
        if(check_square(x - 2, y + 1))
            possible[x - 2][y + 1] = 1;
        if(check_square(x - 2, y - 1))
            possible[x - 2][y - 1] = 1;
        if(check_square(x + 1, y + 2))
            possible[x + 1][y + 2] = 1;
        if(check_square(x + 1, y - 2))
            possible[x + 1][y - 2] = 1;
        if(check_square(x - 1, y + 2))
            possible[x - 1][y + 2] = 1;
        if(check_square(x - 1, y - 2))
            possible[x - 1][y - 2] = 1;
    }
}

void Game::bishop() {
    if(position[x][y] == 'b' || position[x][y] == 'B' ||
            position[x][y] == 'q' || position[x][y] == 'Q') {
        for(int i = 1; x + i < 8 && y + i < 8; i++) {
            if(check_square(x + i, y + i))
                possible[x + i][y + i] = 1;
            if(isalpha(position[x + i][y + i]))
                break;
        }
        for(int i = 1; x + i < 8 && y - i >= 0; i++) {
            if(check_square(x + i, y - i))
                possible[x + i][y - i] = 1;
            if(isalpha(position[x + i][y - i]))
                break;
        }
        for(int i = 1; x - i >= 0 && y + i < 8; i++) {
            if(check_square(x - i, y + i))
                possible[x - i][y + i] = 1;
            if(isalpha(position[x - i][y + i]))
                break;
        }
        for(int i = 1; x - i >= 0 && y - i >= 0; i++) {
            if(check_square(x - i, y - i))
                possible[x - i][y - i] = 1;
            if(isalpha(position[x - i][y - i]))
                break;
        }
    }
}

void Game::rook() {
    if(position[x][y] == 'r' || position[x][y] == 'R' ||
            position[x][y] == 'q' || position[x][y] == 'Q') {
        for(int i = 1; x + i < 8; i++) {
            if(check_square(x + i, y))
                possible[x + i][y] = 1;
            if(isalpha(position[x + i][y]))
                break;
        }
        for(int i = 1; x - i >= 0; i++) {
            if(check_square(x - i, y))
                possible[x - i][y] = 1;
            if(isalpha(position[x - i][y]))
                break;
        }
        for(int i = 1; y + i < 8; i++) {
            if(check_square(x, y + i))
                possible[x][y + i] = 1;
            if(isalpha(position[x][y + i]))
                break;
        }
        for(int i = 1; y - i >= 0; i++) {
            if(check_square(x, y - i))
                possible[x][y - i] = 1;
            if(isalpha(position[x][y - i]))
                break;
        }
    }
}

void Game::king() {
    if(position[x][y] == 'k' || position[x][y] == 'K') {
        if(check_square(x + 1, y))
            possible[x + 1][y] = 1;
        if(check_square(x - 1, y))
            possible[x - 1][y] = 1;
        if(check_square(x, y + 1))
            possible[x][y + 1] = 1;
        if(check_square(x, y - 1))
            possible[x][y - 1] = 1;
        if(check_square(x + 1, y + 1))
            possible[x + 1][y + 1] = 1;
        if(check_square(x + 1, y - 1))
            possible[x + 1][y - 1] = 1;
        if(check_square(x - 1, y + 1))
            possible[x - 1][y + 1] = 1;
        if(check_square(x - 1, y - 1))
            possible[x - 1][y - 1] = 1;
        // castle
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
    ch = false;
    next_check = false;
    int tmp_x = x;
    int tmp_y = y;
    char tmp_piece = position[x1][y1];
    int tmp_possible[8][8];
    position[x1][y1] = position[x][y];
    position[x][y] = ' ';
    std::memcpy(tmp_possible, possible, 64 * sizeof(int));

    for(int i = 0; i < 8 && !next_check; i++)
        for(int j = 0; j < 8 && !next_check; j++)
            if((turn && islower(position[i][j])) || (!turn && isupper(position[i][j]))) {
                x = i;
                y = j;
                reset_possible();
                pawn();
                knight();
                bishop();
                rook();
                king();
            }
    x = tmp_x;
    y = tmp_y;
    position[x][y] = position[x1][y1];
    position[x1][y1] = tmp_piece;
    std::memcpy(possible, tmp_possible, 64 * sizeof(int));
    ch = true;
    return next_check;
}
void Game::end() {
    mate = 1;
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++)
            if((turn && isupper(position[i][j])) || (!turn && islower(position[i][j]))) {
                x = i;
                y = j;
                reset_possible();
                pawn();
                knight();
                bishop();
                rook();
                king();
            }
    if(mate && check(-1, -1)) {
        mate++;
        if(turn)
            mate++;
    }
}
