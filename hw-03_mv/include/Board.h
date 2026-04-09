#ifndef BOARD_H
#define BOARD_H

#include <vector>

const int SIZE = 10;
const int WIN_CONDITION = 5;

enum class Player {
    NONE, NOUGHT, CROSS
};

enum class GameState {
    IN_PROGRESS, O_WINS, X_WINS, DRAW
};

class Board {
private:
    std::vector<std::vector<Player>> grid;
    GameState gameState;
    size_t occupiedCells = 0;
public:
    Player checkWin();
    bool isBoardFull() const;
    Board();
    bool move(int x, int y, Player player);
    GameState getState() const;
    const std::vector<std::vector<Player>>& getGrid() const;

    void reset();

};

#endif // BOARD_H
