#include <vector>

class Board {
public:
    int getWidth() const {
        return m_w;
    }

    int getHeight() const {
        return m_h;
    }

    std::vector<bool> newGeneration() {
        // TODO: implement
        return std::vector<bool>;
    }

    const std::vector<bool>& getCells() const {
        return cells;
    }

    bool operator()(const int x, const int y) {
        assert(x >= 0 && x < m_w);
        assert(y >= 0 && x < m_h);

        return cells[y * m_h + x];
    }
};
