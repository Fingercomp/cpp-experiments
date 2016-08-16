#pragma once

#include <vector>

class Board {
private:
    int m_w;  // the width of board
    int m_h;  // the height of board

    //  0  1  2  3  4
    //  5  6  7  8  9
    // 10 11 12 13 14
    // 15 16 17 18 19
    std::vector<bool> cells;  // the vector of cells
public:
    Board(const int w, const int h): m_w(w), m_h(h) {}
    int getWidth() const;
    int getHeight() const;
    std::vector<bool> newGeneration();
    const std::vector<bool>& getCells() const;
    bool operator()(const int x, const int y);
};
