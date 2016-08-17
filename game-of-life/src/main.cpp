#include <string>

#include <SFML/Graphics.hpp>

#include "board.hpp"
#include "graphics.hpp"


int main() {
    Board board(10, 10);
    Tilemap tilemap(board);
    return 0;
}
