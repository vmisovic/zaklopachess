#include "../lib/ui.hpp"

Ui::Ui() {
    if (!font.loadFromFile("assets/font/Exo2.ttf"))
        std::cout << "Failed to open Exo2.ttf" << std::endl;

    newgame = false;
    playing = false;
    paused = false;
    rotation = true;
    sound = true;
    perspective = true;
    coordinate = true;
    options_menu = false;

    button_color = Color(0x292E42FF);
    inactive_button_color = Color(0x16161EFF);

    text.setFont(font);
    text.setCharacterSize(20);
    text.setStyle(sf::Text::Bold);
    text.setFillColor(Color(0xC0CAF5FF));

    // PAUSE
    button_pause.setSize(Vector2f(200.f, 50.f));
    button_pause.setFillColor(button_color);
    button_pause.setPosition(Vector2f(925.f, 750.f));
    text_pause.setFont(font);
    text_pause.setCharacterSize(20);
    text_pause.setStyle(sf::Text::Bold);
    text_pause.setFillColor(Color(0xC0CAF5FF));
    text_pause.setString("PAUSE");
    text_pause.setPosition(Vector2f(990.f, 762.f));

    // NEW GAME
    button_newgame.setSize(Vector2f(200.f, 50.f));
    button_newgame.setFillColor(button_color);
    button_newgame.setPosition(Vector2f(925.f, 150.f));
    text_newgame.setFont(font);
    text_newgame.setCharacterSize(20);
    text_newgame.setStyle(sf::Text::Bold);
    text_newgame.setFillColor(Color(0xC0CAF5FF));
    text_newgame.setString("NEW GAME");
    text_newgame.setPosition(Vector2f(970.f, 162.f));

    // OPTIONS
    button_options.setSize(Vector2f(200.f, 50.f));
    button_options.setFillColor(button_color);
    button_options.setPosition(Vector2f(925.f, 250.f));
    text_options.setFont(font);
    text_options.setCharacterSize(20);
    text_options.setStyle(sf::Text::Bold);
    text_options.setFillColor(Color(0xC0CAF5FF));
    text_options.setString("OPTIONS");
    text_options.setPosition(Vector2f(980.f, 262.f));

    // QUIT
    button_quit.setSize(Vector2f(200.f, 50.f));
    button_quit.setFillColor(button_color);
    button_quit.setPosition(Vector2f(925.f, 350.f));
    text_quit.setFont(font);
    text_quit.setCharacterSize(20);
    text_quit.setStyle(sf::Text::Bold);
    text_quit.setFillColor(Color(0xC0CAF5FF));
    text_quit.setString("QUIT");
    text_quit.setPosition(Vector2f(1000.f, 362.f));

    // RESUME
    button_resume.setSize(Vector2f(200.f, 50.f));
    button_resume.setFillColor(button_color);
    button_resume.setPosition(Vector2f(925.f, 750.f));
    text_resume.setFont(font);
    text_resume.setCharacterSize(20);
    text_resume.setStyle(Text::Bold);
    text_resume.setFillColor(Color(0xC0CAF5FF));
    text_resume.setString("RESUME");
    text_resume.setPosition(Vector2f(980.f, 762.f));

    // ROTATION
    button_rotation.setSize(Vector2f(200.f, 50.f));
    button_rotation.setFillColor(button_color);
    button_rotation.setPosition(Vector2f(925.f, 150.f));
    label_rotation.setFont(font);
    label_rotation.setCharacterSize(16);
    label_rotation.setStyle(sf::Text::Bold);
    label_rotation.setFillColor(Color(0xC0CAF5FF));
    label_rotation.setString("ROTATION");
    label_rotation.setPosition(Vector2f(925.f, 130.f));
    text_rotation.setFont(font);
    text_rotation.setCharacterSize(20);
    text_rotation.setStyle(Text::Bold);
    text_rotation.setString("ON");
    text_rotation.setFillColor(Color(0xC0CAF5FF));
    text_rotation.setPosition(Vector2f(1010.f, 162.f));

    // SOUND
    button_sound.setSize(Vector2f(200.f, 50.f));
    button_sound.setFillColor(button_color);
    button_sound.setPosition(Vector2f(925.f, 350.f));
    label_sound.setFont(font);
    label_sound.setCharacterSize(16);
    label_sound.setStyle(sf::Text::Bold);
    label_sound.setFillColor(Color(0xC0CAF5FF));
    label_sound.setString("SOUND");
    label_sound.setPosition(Vector2f(925.f, 330.f));
    text_sound.setFont(font);
    text_sound.setCharacterSize(20);
    text_sound.setStyle(Text::Bold);
    text_sound.setString("ON");
    text_sound.setFillColor(Color(0xC0CAF5FF));
    text_sound.setPosition(Vector2f(1010.f, 362.f));

    // PERSPECTIVE
    button_perspective.setSize(Vector2f(200.f, 50.f));
    button_perspective.setFillColor(inactive_button_color);
    button_perspective.setPosition(Vector2f(925.f, 250.f));
    label_perspective.setFont(font);
    label_perspective.setCharacterSize(16);
    label_perspective.setStyle(sf::Text::Bold);
    label_perspective.setFillColor(Color(0xC0CAF5FF));
    label_perspective.setString("PERSPECTIVE");
    label_perspective.setPosition(Vector2f(925.f, 230.f));
    text_perspective.setFont(font);
    text_perspective.setCharacterSize(20);
    text_perspective.setStyle(Text::Bold);
    text_perspective.setString("WHITE");
    text_perspective.setFillColor(Color(0xC0CAF5FF));
    text_perspective.setPosition(Vector2f(990.f, 262.f));

    // COORDINATE
    button_coordinate.setSize(Vector2f(200.f, 50.f));
    button_coordinate.setFillColor(button_color);
    button_coordinate.setPosition(Vector2f(925.f, 450.f));
    label_coordinate.setFont(font);
    label_coordinate.setCharacterSize(16);
    label_coordinate.setStyle(sf::Text::Bold);
    label_coordinate.setFillColor(Color(0xC0CAF5FF));
    label_coordinate.setString("COORDINATE");
    label_coordinate.setPosition(Vector2f(925.f, 430.f));
    text_coordinate.setFont(font);
    text_coordinate.setCharacterSize(20);
    text_coordinate.setStyle(Text::Bold);
    text_coordinate.setString("ON");
    text_coordinate.setFillColor(Color(0xC0CAF5FF));
    text_coordinate.setPosition(Vector2f(1010.f, 462.f));

    // OK
    button_ok.setSize(Vector2f(200.f, 50.f));
    button_ok.setFillColor(button_color);
    button_ok.setPosition(Vector2f(925.f, 750.f));
    text_ok.setFont(font);
    text_ok.setCharacterSize(20);
    text_ok.setStyle(Text::Bold);
    text_ok.setFillColor(Color(0xC0CAF5FF));
    text_ok.setString("OK");
    text_ok.setPosition(Vector2f(1010.f, 762.f));

    // WINNER
    winner.setFont(font);
    winner.setCharacterSize(40);
    winner.setStyle(sf::Text::Bold);
    winner.setFillColor(Color(0xC0CAF5FF));

    // DIM BOARD
    pause.setSize(Vector2f(800.f, 800.f));
    pause.setFillColor(Color(0x00404080));
    pause.setPosition(Vector2f(50.f, 50.f));

    // BOARD
    white_square.setSize(Vector2f(100.f, 100.f));
    white_square.setFillColor(Color(0x908F8DFF));
    black_square.setSize(Vector2f(100.f, 100.f));
    black_square.setFillColor(Color(0x6E6D6BFF));
    possible_square.setRadius(25.f);
    possible_square.setFillColor(Color(0x00000040));
    selected_square.setSize(Vector2f(100.0f, 100.0f));
    selected_square.setFillColor(Color(0x7590A1FF));

    // PAWN
    if (!white_pawn.loadFromFile("assets/textures/white_pawn.png"))
        std::cout << "Failed to open white_pawn.png" << std::endl;
    if (!black_pawn.loadFromFile("assets/textures/black_pawn.png"))
        std::cout << "Failed to open black_pawn.png" << std::endl;

    // KNIGHT
    if (!white_knight.loadFromFile("assets/textures/white_knight.png"))
        std::cout << "Failed to open white_knight.png" << std::endl;
    if (!black_knight.loadFromFile("assets/textures/black_knight.png"))
        std::cout << "Failed to open black_knight.png" << std::endl;

    // BISHOP
    if (!white_bishop.loadFromFile("assets/textures/white_bishop.png"))
        std::cout << "Failed to open white_bishop.png" << std::endl;
    if (!black_bishop.loadFromFile("assets/textures/black_bishop.png"))
        std::cout << "Failed to open black_bishop.png" << std::endl;

    // ROOK
    if (!white_rook.loadFromFile("assets/textures/white_rook.png"))
        std::cout << "Failed to open white_rook.png" << std::endl;
    if (!black_rook.loadFromFile("assets/textures/black_rook.png"))
        std::cout << "Failed to open black_rook.png" << std::endl;

    // QUEEN
    if (!white_queen.loadFromFile("assets/textures/white_queen.png"))
        std::cout << "Failed to open white_queen.png" << std::endl;
    if (!black_queen.loadFromFile("assets/textures/black_queen.png"))
        std::cout << "Failed to open black_queen.png" << std::endl;

    // KING
    if (!white_king.loadFromFile("assets/textures/white_king.png"))
        std::cout << "Failed to open white_king.png" << std::endl;
    if (!black_king.loadFromFile("assets/textures/black_king.png"))
        std::cout << "Failed to open black_king.png" << std::endl;

    // SOUND
    if (!move.loadFromFile("assets/sounds/move.flac"))
        std::cout << "Failed to open move.flac" << std::endl;
    if (!capture.loadFromFile("assets/sounds/capture.flac"))
        std::cout << "Failed to open capture.flac" << std::endl;
}

void Ui::play_sound(bool c) {
    if(sound) {
        if (c)
            sound_effect.setBuffer(capture);
        else
            sound_effect.setBuffer(move);
        sound_effect.play();
    }
}

void Ui::draw_coordinate(RenderTarget& window, bool side) {
    int j;
    for(int i = 1; i < 9; i++) {
        if(side) j = 9 - i;
        else j = i;
        text.setString(std::to_string(j));
        text.setPosition(Vector2f(20.f, i * 100.f - 10.f));
        window.draw(text);
        std::string letter(1, 73 - j);
        text.setString(letter);
        text.setPosition(Vector2f(i * 100.f - 5.f, 860.f));
        window.draw(text);
    }
}

void Ui::draw_board(sf::RenderTarget& window, char position[8][8], int possible[8][8], int x, int y) {
    int m, n;
    if(!side) {
        x = 7 - x;
        y = 7 - y;
    }
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if(i == x && j == y) {
                selected_square.setPosition(Vector2f(100.f * j + 50.f, 100.f * i + 50.f));
                window.draw(selected_square);
            }
            else {
                if((i + j + 1) % 2) {
                    white_square.setPosition(Vector2f(100.f * j + 50.f, 100.f * i + 50.f));
                    window.draw(white_square);
                }
                else {
                    black_square.setPosition(Vector2f(100.f * j + 50.f, 100.f * i + 50.f));
                    window.draw(black_square);
                }
            }
        }
    }
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if(side) {
                m = j;
                n = i;
            }
            else {
                m = 7 - j;
                n = 7 - i;
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

void Ui::menu(RenderTarget& window) {
    window.draw(pause);
    if(options_menu) {
        window.draw(label_rotation);
        window.draw(button_rotation);
        window.draw(text_rotation);

        window.draw(label_sound);
        window.draw(button_sound);
        window.draw(text_sound);

        window.draw(label_perspective);
        window.draw(button_perspective);
        window.draw(text_perspective);

        window.draw(label_coordinate);
        window.draw(button_coordinate);
        window.draw(text_coordinate);

        window.draw(button_ok);
        window.draw(text_ok);

        if(!playing) {
            window.draw(winner);
        }
    }
    else {
        window.draw(button_newgame);
        window.draw(text_newgame);

        window.draw(button_options);
        window.draw(text_options);

        window.draw(button_quit);
        window.draw(text_quit);

        if(paused) {
            window.draw(button_resume);
            window.draw(text_resume);
        }

        if(!playing) {
            window.draw(winner);
        }
    }
}

void Ui::draw(RenderTarget& window, char position[8][8], int possible[8][8], int x, int y, bool turn) {
    side = (turn && rotation) || (!rotation && perspective);
    window.clear(Color(0x1A1B26FF));
    draw_board(window, position, possible, x, y);
    if(coordinate)
        draw_coordinate(window, side);
    if(!playing || paused) {
        menu(window);
    }
    else {
        window.draw(button_pause);
        window.draw(text_pause);
    }
}

void Ui::input(int mouse_x, int mouse_y, int *x, int *y, bool turn) {
    if(!playing || paused) {
        if(options_menu) {
            if(button_rotation.getPosition().x < mouse_x && mouse_x < button_rotation.getPosition().x + button_rotation.getSize().x &&
                    button_rotation.getPosition().y < mouse_y && mouse_y < button_rotation.getPosition().y + button_rotation.getSize().y) {
                update_rotation();
            }
            else if(button_sound.getPosition().x < mouse_x && mouse_x < button_sound.getPosition().x + button_sound.getSize().x &&
                    button_sound.getPosition().y < mouse_y && mouse_y < button_sound.getPosition().y + button_sound.getSize().y) {
                update_sound();
            }
            else if(button_perspective.getPosition().x < mouse_x && mouse_x < button_perspective.getPosition().x + button_perspective.getSize().x &&
                    button_perspective.getPosition().y < mouse_y && mouse_y < button_perspective.getPosition().y + button_perspective.getSize().y) {
                update_perspective();
            }
            else if(button_coordinate.getPosition().x < mouse_x && mouse_x < button_coordinate.getPosition().x + button_coordinate.getSize().x &&
                    button_coordinate.getPosition().y < mouse_y && mouse_y < button_coordinate.getPosition().y + button_coordinate.getSize().y) {
                update_coordinate();
            }
            else if(button_ok.getPosition().x < mouse_x && mouse_x < button_ok.getPosition().x + button_ok.getSize().x &&
                    button_ok.getPosition().y < mouse_y && mouse_y < button_ok.getPosition().y + button_ok.getSize().y) {
                options_menu = false;
            }
        }
        else {
            if(button_newgame.getPosition().x < mouse_x && mouse_x < button_newgame.getPosition().x + button_newgame.getSize().x &&
                    button_newgame.getPosition().y < mouse_y && mouse_y < button_newgame.getPosition().y + button_newgame.getSize().y) {
                newgame = true;
                paused = false;
            }
            else if(button_options.getPosition().x < mouse_x && mouse_x < button_options.getPosition().x + button_options.getSize().x &&
                    button_options.getPosition().y < mouse_y && mouse_y < button_options.getPosition().y + button_options.getSize().y) {
                options_menu = true;
            }
            else if(button_quit.getPosition().x < mouse_x && mouse_x < button_quit.getPosition().x + button_quit.getSize().x &&
                    button_quit.getPosition().y < mouse_y && mouse_y < button_quit.getPosition().y + button_quit.getSize().y) {
                exit(0);
            }
            else if(button_resume.getPosition().x < mouse_x && mouse_x < button_resume.getPosition().x + button_resume.getSize().x &&
                    button_resume.getPosition().y < mouse_y && mouse_y < button_resume.getPosition().y + button_resume.getSize().y) {
                paused = false;
            }
        }
    }
    else {
        *x = (mouse_y - 50) / 100;
        *y = (mouse_x - 50) / 100;
        if(*x >= 0 && *x < 8 && *y >= 0 && *y < 8 && !paused) {
            if(!side) {
                *x = 7 - *x;
                *y = 7 - *y;
            }
        }
        else {
            *x = -1;
            *y = -1;
        }
        if(button_pause.getPosition().x < mouse_x && mouse_x < button_pause.getPosition().x + button_pause.getSize().x &&
                button_pause.getPosition().y < mouse_y && mouse_y < button_pause.getPosition().y + button_pause.getSize().y) {
            paused = true;
        }
    }
}

void Ui::update_rotation() {
    rotation = !rotation;
    if(rotation) {
        text_rotation.setString("ON");
        text_rotation.setPosition(Vector2f(1010.f, 162.f));
        button_perspective.setFillColor(inactive_button_color);
    }
    else {
        text_rotation.setString("OFF");
        text_rotation.setPosition(Vector2f(1005.f, 162.f));
        button_perspective.setFillColor(button_color);
    }

}

void Ui::update_sound() {
    sound = !sound;
    if(sound) {
        text_sound.setString("ON");
        text_sound.setPosition(Vector2f(1010.f, 362.f));
    }
    else {
        text_sound.setString("OFF");
        text_sound.setPosition(Vector2f(1005.f, 362.f));
    }
}

void Ui::update_perspective() {
    perspective = !perspective;
    if(perspective)
        text_perspective.setString("WHITE");
    else
        text_perspective.setString("BLACK");
}

void Ui::update_coordinate() {
    coordinate = !coordinate;
    if(coordinate) {
        text_coordinate.setString("ON");
        text_coordinate.setPosition(Vector2f(1010.f, 462.f));
    }
    else {
        text_coordinate.setString("OFF");
        text_coordinate.setPosition(Vector2f(1005.f, 462.f));
    }
}

bool Ui::start_game() {
    if(newgame) {
        playing = true;
        newgame = false;
        return true;
    }
    return false;
}

void Ui::end_game(bool end, bool check, bool turn) {
    if(end) {
        playing = false;
        if(check) {
            if(turn)
                winner.setString("CHECKMATE BLACK WON");
            else
                winner.setString("CHECKMATE WHITE WON");
            winner.setPosition(Vector2f(215.f, 422.f));
        }
        else {
            winner.setString("STALEMATE DRAW");
            winner.setPosition(Vector2f(275.f, 422.f));
        }
    }
}
