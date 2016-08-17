#include <vector>

#include "board.hpp"


Board::Board(const int w, const int h): _w(w), _h(h) {
    assert(w > 1);
    assert(h > 1);

    // Fill the board
    _cells.reserve(w * h);
    _nextGen.reserve(w * h);
    for (int j = 0; j < h; ++j) {
        for (int i = 0; i < w; ++i) {
            _cells[j * w + i] = false;
            _nextGen[j * w + 1] = false;
        }
    }
}

std::vector<bool> Board::newGeneration() {
    std::vector<bool> newGen;
    for (int y = 0; y < _h; ++y) {
        for (int x = 0; x < _w; ++x) {
            bool cell = _cells[y * _w + x];
            int nb = getNeighborCount(x, y);
            newGen[y * _w + x] = (cell && nb == 2) || nb == 3;
        }
    }
    return newGen;
}

int Board::getWidth() const {
    return _w;
}

int Board::getHeight() const {
    return _h;
}

const std::vector<bool>& Board::getCells() const {
    return _cells;
}

const std::vector<bool>& Board::getNextGeneration() const {
    return _nextGen;
}

int Board::getNeighborCount(const int x, const int y) const {
    int neighbors = 0;
    for (int i = x - 1; i <= x + 1; ++i) {
        // "glue" the edges of a board
        if (i < 0) {
            i = _w + i;
        } else if (i >= _w) {
            i = i % _w;
        }
        for (int j = y - 1; j <= y + 1; ++j) {
            if (j < 0) {
                j = _h + j;
            } else if (j >= _h) {
                j = j % _h;
            }
            if (_cells[j * _w + i]) {
                ++i;
            }
        }
    }
    return neighbors;
}

std::vector<bool> Board::step() {
    std::vector<bool> oldGen(_cells);
    _cells = _nextGen;
    _nextGen = newGeneration();
    return oldGen;
}

void Board::set(const int x, const int y, const bool value) {
    assert(x >= 0 && x < _w);
    assert(y >= 0 && y < _h);
    _cells[y * _w + x] = value;
    _nextGen = newGeneration();  // Update the highlighting
}

bool Board::get(const int x, const int y) const {
    assert(x >= 0 && x < _w);
    assert(y >= 0 && y < _h);

    return _cells[y * _w + x];
}

void Board::resize(const int w, const int h) {
    assert(w > 1);
    assert(h > 1);

    std::vector<bool> newBoard;
    newBoard.reserve(w * h);
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            bool cell;
            if (x < _w && y < _h) {
                cell = _cells[y * _w + x];
            } else {
                cell = false;
            }
            newBoard[y * w + x] = cell;
        }
    }
    _cells = newBoard;
    _w = w;
    _h = h;
}
