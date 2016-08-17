#include <iostream>
#include <cmath>
#include <map>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "board.hpp"
#include "graphics.hpp"


int main() {
    Board board(10, 10);
    CellTilemap cellTilemap(board);
    sf::Texture texture;
    std::vector<std::pair<Tile, sf::Color>> tilesetNumbers;
    std::vector<uint8_t> tilesetBytes;
    createTileset(graphicsSettings::colors, tilesetNumbers, tilesetBytes, texture);
    Tilemap tilemap(cellTilemap, texture, tilesetNumbers);
    sf::RenderWindow window(sf::VideoMode(800, 600), "Game of Life");
    window.setVerticalSyncEnabled(true);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::Resized: {
                    sf::FloatRect visibleArea(0, 0, static_cast<float>(event.size.width), static_cast<float>(event.size.height));
                    window.setView(sf::View(visibleArea));
                    cellTilemap.resize(ceil(static_cast<float>(event.size.width) / graphicsSettings::cellWidth), ceil(static_cast<float>(event.size.height) / graphicsSettings::cellHeight));
                }
                default:
                    break;
            }
        }
        window.clear();
        tilemap.update();
        window.draw(tilemap);
        window.display();
    }
    return 0;
}
