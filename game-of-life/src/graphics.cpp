#include "graphics.hpp"
#include "utils.hpp"


CellTilemap::CellTilemap(Board &board): _board(board) {
    _w = _board.getWidth();
    _h = _board.getHeight();
    fill(_tiles, _w * _h);
    update();
}

void CellTilemap::update() {
    int newWidth = _board.getWidth();
    int newHeight = _board.getHeight();
    if (_w != newWidth || _h != newHeight) {
        // The board was resized
        _w = newWidth;
        _h = newHeight;
        _tiles.clear();
        fill(_tiles, _w * _h);
    }
    const std::vector<bool> thisGen = _board.getCells();
    const std::vector<bool> nextGen = _board.getNextGeneration();
    for (int j = 0; j < _h; ++j) {
        for (int i = 0; i < _w; ++i) {
            int index = j * _w + i;
            bool thisGenCell = thisGen[index];
            bool nextGenCell = nextGen[index];
            if (thisGenCell && nextGenCell) {
                _tiles.at(index) = Tile::ALIVE;
            } else if (thisGenCell && !nextGenCell) {
                _tiles.at(index) = Tile::DEAD_NEXT_GEN;
            } else if (!thisGenCell && nextGenCell) {
                _tiles.at(index) = Tile::ALIVE_NEXT_GEN;
            } else if (!thisGenCell && !nextGenCell) {
                _tiles.at(index) = Tile::DEAD;
            }
        }
    }
}

Tile CellTilemap::get(const int x, const int y) const {
    return _tiles[y * _w + x];
}

void CellTilemap::set(const int x, const int y, const bool value) {
    _board.set(x, y, value);
    update();
}

void CellTilemap::resize(const int x, const int y) {
    _board.resize(x, y);
    update();
}

int CellTilemap::getWidth() const {
    return _w;
}

int CellTilemap::getHeight() const {
    return _h;
}


Tilemap::Tilemap(CellTilemap &tilemap, sf::Texture &tileset, std::vector<std::pair<Tile, sf::Color>> &tileNumbers)
        : _tilemap(tilemap), _tileset(tileset), _tileNumbers(tileNumbers) {}

void Tilemap::update() {
    _tilemap.update();
    int w = _tilemap.getWidth();
    int h = _tilemap.getHeight();

    _vertices.setPrimitiveType(sf::Quads);
    _vertices.resize(w * h * 4);

    for (int i = 0; i < w; ++i) {
        for (int j = 0; j < h; ++j) {
            Tile tile = _tilemap.get(i, j);
            int num = 0;
            for (auto item: _tileNumbers) {
                if (item.first == tile) {
                    break;
                }
                ++num;
            }

            sf::Vertex *quad = &_vertices[(i + j * w) * 4];
            quad[0].position = sf::Vector2f(i * graphicsSettings::cellWidth, j * graphicsSettings::cellHeight);
            quad[1].position = sf::Vector2f((i + 1) * graphicsSettings::cellWidth, j * graphicsSettings::cellHeight);
            quad[2].position = sf::Vector2f((i + 1) * graphicsSettings::cellWidth, (j + 1) * graphicsSettings::cellHeight);
            quad[3].position = sf::Vector2f(i * graphicsSettings::cellWidth, (j + 1) * graphicsSettings::cellHeight);

            quad[0].texCoords = sf::Vector2f(num, 0);
            quad[1].texCoords = sf::Vector2f(num, 0);
            quad[2].texCoords = sf::Vector2f(num, 0);
            quad[3].texCoords = sf::Vector2f(num, 0);
        }
    }
}

void Tilemap::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = &_tileset;
    target.draw(_vertices, states);
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

// Creates a tileset
void createTileset(const std::map<Tile, sf::Color> &colors, std::vector<std::pair<Tile, sf::Color>> &result, std::vector<uint8_t> &colorVec, sf::Texture &texture) {
    for (int i = 0; i < graphicsSettings::cellHeight; ++i) {
        for (auto &c: colors) {
            for (int j = 0; j < graphicsSettings::cellWidth; ++j) {
                colorVec.push_back(c.second.r);
                colorVec.push_back(c.second.g);
                colorVec.push_back(c.second.b);
                colorVec.push_back(c.second.a);
            }
            if (i == 0) {
                result.push_back(c);
            }
        }
    }
    texture.create(colorVec.size() * graphicsSettings::cellWidth, graphicsSettings::cellHeight);
    texture.update(&colorVec[0]);
}
