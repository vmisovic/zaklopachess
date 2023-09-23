#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

using namespace sf;

class Board {
    Color white;
    Color black;
    RectangleShape squares[8][8];
    public:
    Board();
    void draw(sf::RenderTarget& window);
};

