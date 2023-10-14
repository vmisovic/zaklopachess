#ifndef ZAKLOPACHESS_HPP
#define ZAKLOPACHESS_HPP

#include <SFML/Graphics.hpp>
#include "game.hpp"
#include "ui.hpp"
#include "server.hpp"

struct ZaklopaChess {
private:
    Game game;
    Ui ui;

    void input(int x, int y);
public:
    void play();
};

#endif
