#include "zaklopachess.hpp"

void ZaklopaChess::input (int mouse_x, int mouse_y) {
    int x, y;
    ui.input(mouse_x, mouse_y, &x, &y, game.turn);
    if(ui.start_game()) game.new_game();
    if(ui.playing && !ui.paused) {
        if(mouse_x < 850 && mouse_y < 850) game.play(x, y);
        if(game.moved) {
            ui.play_sound(game.capture);
            ui.end_game(game.mate);
        }
    }
}

void ZaklopaChess::play() {
    RenderWindow window(VideoMode(1200, 900), "zaklopachess", Style::Close);
    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if(event.type == Event::MouseButtonPressed){
                if(event.mouseButton.button == Mouse::Left) {
                    input(event.mouseButton.x * 1200 / window.getSize().x, event.mouseButton.y * 900 / window.getSize().y);
                }
            }
        }
        ui.draw(window, game.position, game.possible, game.x, game.y, game.turn);
        window.display();
    }
}
