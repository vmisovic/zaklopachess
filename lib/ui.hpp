#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

using namespace sf;

struct Ui {
    private:
    Color button_color;
    Color inactive_button_color;

    Font font;
    Text text;

    Text text_pause;
    RectangleShape button_pause;

    Text text_newgame;
    Text text_options;
    Text text_quit;
    Text text_resume;
    RectangleShape button_newgame;
    RectangleShape button_options;
    RectangleShape button_quit;
    RectangleShape button_resume;

    Text label_rotation;
    Text label_sound;
    Text label_perspective;
    Text text_rotation;
    Text text_sound;
    Text text_perspective;
    Text text_ok;
    RectangleShape button_rotation;
    RectangleShape button_sound;
    RectangleShape button_perspective;
    RectangleShape button_ok;

    RectangleShape pause;

    bool sound;
    bool rotation;
    bool perspective;
    bool playing;
    bool paused;
    bool newgame;
    bool options_menu;

    void draw_coordinate(RenderTarget& window);
    void draw_rotated_coordinate(RenderTarget& window);
    void menu(RenderTarget& window);

    void update_rotation();
    void update_sound();
    void update_perspective();

    public:
    Ui();
    void draw(RenderTarget& window, bool rotation);
    void update_settings(bool *paused, bool *rotation, bool *sound, bool *perspective);
    void input(int mouse_x, int mouse_y);
    bool start_game();
    void show_menu();
};
