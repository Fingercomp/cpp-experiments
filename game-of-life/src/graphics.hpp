#pragma once

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <utility>

#include <SFML/Graphics.hpp>

#include "board.hpp"
#include "cmake-options.hpp.in"


enum class Tile {
    DEAD,
    DEAD_NEXT_GEN,
    ALIVE,
    ALIVE_NEXT_GEN
};


namespace graphicsSettings {
    const int cellWidth = 5;
    const int cellHeight = 5;
    const std::map<Tile, sf::Color> colors {
        {Tile::DEAD, sf::Color(0x00, 0x00, 0x00)},
        {Tile::DEAD_NEXT_GEN, sf::Color(0x80, 0x00, 0x00)},
        {Tile::ALIVE, sf::Color(0xff, 0xff, 0xff)},
        {Tile::ALIVE_NEXT_GEN, sf::Color(0x00, 0x80, 0x00)}
    };
}


class CellTilemap {
private:
    Board &_board;
    std::vector<Tile> _tiles;
    int _w;
    int _h;
public:
    CellTilemap(Board &board);
    void update();
    Tile get(const int x, const int y) const;
    void set(const int x, const int y, const bool value);
    void resize(const int x, const int y);
    int getWidth() const;
    int getHeight() const;
};

class Tilemap: public sf::Drawable, public sf::Transformable {
private:
    CellTilemap _tilemap;
    sf::Texture _tileset;
    std::vector<std::pair<Tile, sf::Color>> _tileNumbers;
    sf::VertexArray _vertices;
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
public:
    Tilemap(CellTilemap &tilemap, sf::Texture &tileset, std::vector<std::pair<Tile, sf::Color>> &tileNumbers);
    void update();
};


sf::Sprite loadSprite(std::string filename);
sf::Sprite loadSprite(sf::Texture &texture);

sf::Font loadFont(std::string filename);

void createTileset(const std::map<Tile, sf::Color> &colors, std::vector<std::pair<Tile, sf::Color>> &result, sf::Uint8 *pixels, sf::Texture &texture);
