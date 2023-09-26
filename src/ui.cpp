#include "../lib/ui.hpp"

Ui::Ui() {
    if (!font.loadFromFile("assets/font/Exo2.ttf"))
        std::cout << "Failed to open Exo2.ttf" << std::endl;

    newgame = false;
    playing = false;
    paused = false;
    rotation = false;
    sound = false;
    perspective = false;
    options_menu = false;

    button_color = Color(0xF92E42FF);
    inactive_button_color = Color(0x292E42FF);

    text.setFont(font);
    text.setCharacterSize(36);
    text.setStyle(sf::Text::Bold);
    text.setFillColor(Color(0xC0CAF5FF));

    // PAUSE
    button_pause.setSize(Vector2f(228.f, 96.f));
    button_pause.setFillColor(button_color);
    button_pause.setPosition(Vector2f(1200.f, 900.f));
    text_pause.setFont(font);
    text_pause.setCharacterSize(36);
    text_pause.setStyle(sf::Text::Bold);
    text_pause.setFillColor(Color(0xC0CAF5FF));
    text_pause.setString("PAUSE");
    text_pause.setPosition(Vector2f(1256.f, 926.f));

    // NEW GAME
    button_newgame.setSize(Vector2f(228.f, 96.f));
    button_newgame.setFillColor(button_color);
    button_newgame.setPosition(Vector2f(1200.f, 150.f));
    text_newgame.setFont(font);
    text_newgame.setCharacterSize(36);
    text_newgame.setStyle(sf::Text::Bold);
    text_newgame.setFillColor(Color(0xC0CAF5FF));
    text_newgame.setString("NEW GAME");
    text_newgame.setPosition(Vector2f(1220.f, 176.f));

    // OPTIONS
    button_options.setSize(Vector2f(228.f, 96.f));
    button_options.setFillColor(button_color);
    button_options.setPosition(Vector2f(1200.f, 300.f));
    text_options.setFont(font);
    text_options.setCharacterSize(36);
    text_options.setStyle(sf::Text::Bold);
    text_options.setFillColor(Color(0xC0CAF5FF));
    text_options.setString("OPTIONS");
    text_options.setPosition(Vector2f(1236.f, 326.f));

    // QUIT
    button_quit.setSize(Vector2f(228.f, 96.f));
    button_quit.setFillColor(Color(0xf92E42FF));
    button_quit.setPosition(Vector2f(1200.f, 450.f));
    text_quit.setFont(font);
    text_quit.setCharacterSize(36);
    text_quit.setStyle(sf::Text::Bold);
    text_quit.setFillColor(Color(0xC0CAF5FF));
    text_quit.setString("QUIT");
    text_quit.setPosition(Vector2f(1272.f, 476.f));

    // RESUME
    button_resume.setSize(Vector2f(228.f, 96.f));
    button_resume.setFillColor(Color(0xf92E42FF));
    button_resume.setPosition(Vector2f(1200.f, 900.f));
    text_resume.setFont(font);
    text_resume.setCharacterSize(36);
    text_resume.setStyle(Text::Bold);
    text_resume.setFillColor(Color(0xC0CAF5FF));
    text_resume.setString("RESUME");
    text_resume.setPosition(Vector2f(1240.f, 926.f));

    // ROTATION
    button_rotation.setSize(Vector2f(228.f, 96.f));
    button_rotation.setFillColor(button_color);
    button_rotation.setPosition(Vector2f(1200.f, 150.f));
    label_rotation.setFont(font);
    label_rotation.setCharacterSize(24);
    label_rotation.setStyle(sf::Text::Bold);
    label_rotation.setFillColor(Color(0xC0CAF5FF));
    label_rotation.setString("ROTATION");
    label_rotation.setPosition(Vector2f(1200.f, 120.f));
    text_rotation.setFont(font);
    text_rotation.setCharacterSize(36);
    text_rotation.setStyle(Text::Bold);
    text_rotation.setFillColor(Color(0xC0CAF5FF));

    // SOUND
    button_sound.setSize(Vector2f(228.f, 96.f));
    button_sound.setFillColor(button_color);
    button_sound.setPosition(Vector2f(1200.f, 300.f));
    label_sound.setFont(font);
    label_sound.setCharacterSize(24);
    label_sound.setStyle(sf::Text::Bold);
    label_sound.setFillColor(Color(0xC0CAF5FF));
    label_sound.setString("SOUND");
    label_sound.setPosition(Vector2f(1200.f, 270.f));
    text_sound.setFont(font);
    text_sound.setCharacterSize(36);
    text_sound.setStyle(Text::Bold);
    text_sound.setFillColor(Color(0xC0CAF5FF));

    // PERSPECTIVE
    button_perspective.setSize(Vector2f(228.f, 96.f));
    button_perspective.setFillColor(Color(0xf92E42FF));
    button_perspective.setPosition(Vector2f(1200.f, 450.f));
    label_perspective.setFont(font);
    label_perspective.setCharacterSize(24);
    label_perspective.setStyle(sf::Text::Bold);
    label_perspective.setFillColor(Color(0xC0CAF5FF));
    label_perspective.setString("PERSPECTIVE");
    label_perspective.setPosition(Vector2f(1200.f, 420.f));
    text_perspective.setFont(font);
    text_perspective.setCharacterSize(36);
    text_perspective.setStyle(Text::Bold);
    text_perspective.setFillColor(Color(0xC0CAF5FF));

    // OK
    button_ok.setSize(Vector2f(228.f, 96.f));
    button_ok.setFillColor(Color(0xf92E42FF));
    button_ok.setPosition(Vector2f(1200.f, 900.f));
    text_ok.setFont(font);
    text_ok.setCharacterSize(36);
    text_ok.setStyle(Text::Bold);
    text_ok.setFillColor(Color(0xC0CAF5FF));
    text_ok.setString("OK");
    text_ok.setPosition(Vector2f(1290.f, 926.f));

    // DIM BOARD
    pause.setSize(Vector2f(1024.f, 1024.f));
    pause.setFillColor(Color(0x00408080));
    pause.setPosition(Vector2f(64.f, 64.f));

    update_rotation();
    update_sound();
    update_perspective();
}

void Ui::update_settings(bool *paused_game, bool *rotation_game, bool *sound_game, bool *perspective_game) {
    *paused_game = paused;
    *rotation_game = rotation;
    *sound_game = sound;
    *perspective_game = perspective;
}

void Ui::draw_coordinate(RenderTarget& window) {
    for(int i = 1; i < 9; i++) {
        text.setString(std::to_string(i));
        text.setPosition(Vector2f(24.f, (9 - i) * 128.f - 16.f));
        window.draw(text);
        std::string letter(1, i + 64);
        text.setString(letter);
        text.setPosition(Vector2f(i * 128.f - 12.f, 1096.f));
        window.draw(text);
    }
}

void Ui::draw_rotated_coordinate(RenderTarget& window) {
    for(int i = 1; i < 9; i++) {
        text.setString(std::to_string(i));
        text.setPosition(Vector2f(24.f, i * 128.f - 16.f));
        window.draw(text);
        std::string letter(1, 73 - i);
        text.setString(letter);
        text.setPosition(Vector2f(i * 128.f - 12.f, 1096.f));
        window.draw(text);
    }
}

void Ui::draw(RenderTarget& window, bool rotation) {
    if(rotation)
        draw_coordinate(window);
    else
        draw_rotated_coordinate(window);

    if(!playing || paused) {
        menu(window);
    }
    else {
        window.draw(button_pause);
        window.draw(text_pause);
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

        window.draw(button_ok);
        window.draw(text_ok);
    }
    else {
        // NEW GAME
        window.draw(button_newgame);
        window.draw(text_newgame);

        // OPTIONS
        window.draw(button_options);
        window.draw(text_options);

        // QUIT
        window.draw(button_quit);
        window.draw(text_quit);

        // RESUME
        if(paused) {
            window.draw(button_resume);
            window.draw(text_resume);
        }
    }
}

void Ui::input(int mouse_x, int mouse_y) {
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
        if(button_pause.getPosition().x < mouse_x && mouse_x < button_pause.getPosition().x + button_pause.getSize().x &&
                button_pause.getPosition().y < mouse_y && mouse_y < button_pause.getPosition().y + button_pause.getSize().y) {
            show_menu();
        }
    }
}

void Ui::update_rotation() {
    rotation = !rotation;
    if(rotation) {
        text_rotation.setString("ON");
        text_rotation.setPosition(Vector2f(1286.f, 176.f));
        button_perspective.setFillColor(inactive_button_color);
    }
    else {
        text_rotation.setString("OFF");
        text_rotation.setPosition(Vector2f(1280.f, 176.f));
        button_perspective.setFillColor(button_color);
    }

}

void Ui::update_sound() {
    sound = !sound;
    if(sound) {
        text_sound.setString("ON");
        text_sound.setPosition(Vector2f(1286.f, 326.f));
    }
    else {
        text_sound.setString("OFF");
        text_sound.setPosition(Vector2f(1280.f, 326.f));
    }
}

void Ui::update_perspective() {
    perspective = !perspective;
    if(perspective) {
        text_perspective.setString("WHITE");
        text_perspective.setPosition(Vector2f(1256.f, 476.f));
    }
    else {
        text_perspective.setString("BLACK");
        text_perspective.setPosition(Vector2f(1256.f, 476.f));
    }
}

void Ui::show_menu() {
    if(playing)
        paused = true;
}

bool Ui::start_game() {
    if(newgame) {
        playing = true;
        newgame = false;
        return true;
    }
    return false;
}
