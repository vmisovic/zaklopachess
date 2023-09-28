#include <SFML/Graphics.hpp>
#include "../lib/game.hpp"

using namespace sf;

int main() {
    RenderWindow window(VideoMode(1200, 900), "zaklopachess", Style::Close);
    window.setFramerateLimit(60);
    window.setSize(sf::Vector2u(1200, 900));

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
                    game.move(event.mouseButton.y * 900 / window.getSize().y, event.mouseButton.x * 1200 / window.getSize().x);
                }
            }
        }
        game.draw(window);
        window.display();
    }
    return 0;
}
