#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

#include "board.hpp"
#include "graphics.hpp"


int main() {
    Board board(10, 10);
    Tilemap tilemap(board);

    tilemap.resize(20, 20);
    std::cout << board.getWidth() << "\n" << board.getWidth() << std::endl;
    return 0;
}
