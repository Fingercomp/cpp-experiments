#include "graphics.hpp"


Tilemap::Tilemap(Board &board): _board(board) {
    _w = _board.getWidth();
    _h = _board.getHeight();
    _tiles.reserve(_w * _h);
    update();
}

void Tilemap::update() {
    int newWidth = _board.getWidth();
    int newHeight = _board.getHeight();
    if (_w == newWidth && _h == newHeight) {
        // The board was resized
        _w = newWidth;
        _h = newHeight;
        _tiles.clear();
        _tiles.reserve(newWidth * newHeight);
    }
    const std::vector<bool> thisGen = _board.getCells();
    const std::vector<bool> nextGen = _board.getNextGeneration();
    for (int j = 0; j < _h; ++j) {
        for (int i = 0; i < _w; ++i) {
            int index = j * _w + i;
            bool thisGenCell = thisGen[index];
            bool nextGenCell = nextGen[index];
            if (thisGenCell && nextGenCell) {
                _tiles[index] = Tile::ALIVE;
            } else if (thisGenCell && !nextGenCell) {
                _tiles[index] = Tile::DEAD_NEXT_GEN;
            } else if (!thisGenCell && nextGenCell) {
                _tiles[index] = Tile::ALIVE_NEXT_GEN;
            } else if (!thisGenCell && !nextGenCell) {
                _tiles[index] = Tile::DEAD;
            }
        }
    }
}

Tile Tilemap::get(const int x, const int y) const {
    return _tiles[y * _w + x];
}

void Tilemap::set(const int x, const int y, const bool value) {
    _board.set(x, y, value);
    update();
}

void Tilemap::resize(const int x, const int y) {
    _board.resize(x, y);
    update();
}


sf::Sprite loadSprite(std::string filename) {
    static sf::Texture texture;
    if (!texture.loadFromFile(RESOURCES_DIR +
                              static_cast<std::string>("/textures/") +
                              filename)) {
        std::cerr << "Could not load the texture: " << filename << "\n";
    }

    texture.setSmooth(true);

    return sf::Sprite(texture);
}

sf::Sprite loadSprite(sf::Texture &texture) {
    return sf::Sprite(texture);
}

sf::Font loadFont(std::string filename) {
    sf::Font font;
    if (!font.loadFromFile(RESOURCES_DIR +
                           static_cast<std::string>("/fonts/") + filename)) {
        std::cerr << "Could not load the file: " << filename << "\n";
    }

    return font;
}
