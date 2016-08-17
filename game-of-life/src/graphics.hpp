#pragma once

#include <iostream>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "board.hpp"
#include "cmake-options.hpp.in"


enum class Tile {
    DEAD,
    DEAD_NEXT_GEN,
    ALIVE,
    ALIVE_NEXT_GEN
};


class Tilemap {
private:
    Board &_board;
    std::vector<Tile> _tiles;
    int _w;
    int _h;
public:
    Tilemap(Board &board);
    void update();
    Tile get(const int x, const int y) const;
    void set(const int x, const int y, const bool value);
    void resize(const int x, const int y);
};


sf::Sprite loadSprite(std::string filename);
sf::Sprite loadSprite(sf::Texture &texture);

sf::Font loadFont(std::string filename);
