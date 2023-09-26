#include <SFML/Graphics.hpp>
#include "../lib/game.hpp"

using namespace sf;

int main() {
    RenderWindow window(VideoMode(1536, 1152), "zaklopachess");
    window.setFramerateLimit(60);

    Game game;
    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();

            if (Keyboard::isKeyPressed(Keyboard::Escape))
                game.show_menu();

            if(event.type == Event::MouseButtonPressed){
                if(event.mouseButton.button == Mouse::Left) {
                    game.move(event.mouseButton.y, event.mouseButton.x);
                }
            }
        }

        window.clear();
        window.clear(Color(0x1A1B26FF));
        game.draw(window);
        window.display();
    }
    return 0;
}
