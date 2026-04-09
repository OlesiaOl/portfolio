#include "Board.h"

const std::vector<std::vector<Player>>& Board::getGrid() const {
    return grid;
}

void Board::reset() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            grid[i][j] = Player::NONE;
        }
    }
    occupiedCells = 0;
    gameState = GameState::IN_PROGRESS;
}

Board::Board() : grid(SIZE, std::vector<Player>(SIZE, Player::NONE)),
    gameState(GameState::IN_PROGRESS) {}

bool Board::move(int x, int y, Player player) {
    if (x >= 0 && y >= 0 && x < SIZE && y < SIZE && grid[x][y] == Player::NONE) {
        grid[x][y] = player;
        ++occupiedCells;

        Player winner = checkWin();
        if (winner != Player::NONE) {
            gameState = (winner == Player::NOUGHT) ? GameState::O_WINS : GameState::X_WINS;
        } else if (isBoardFull()) {
            gameState = GameState::DRAW;
        }

        return true;
    }
    return false;
}

GameState Board::getState() const {
    return gameState;
}

Player Board::checkWin() {
    for (size_t i = 0; i < SIZE; i++) {
        for (size_t j = 0; j < SIZE; j++) {
            Player player = grid[i][j];
            if (player == Player::NONE) continue;

            if (j <= SIZE - WIN_CONDITION) {
                bool win = true;
                for (size_t k = 0; k < WIN_CONDITION; k++) {
                    if (grid[i][j + k] != player) {
                        win = false;
                        break;
                    }
                }
                if (win) return player;
            }

            if (i <= SIZE - WIN_CONDITION) {
                bool win = true;
                for (size_t k = 0; k < WIN_CONDITION; k++) {
                    if (grid[i + k][j] != player) {
                        win = false;
                        break;
                    }
                }
                if (win) return player;
            }

            if (i <= SIZE - WIN_CONDITION && j <= SIZE - WIN_CONDITION) {
                bool win = true;
                for (size_t k = 0; k < WIN_CONDITION; k++) {
                    if (grid[i + k][j + k] != player) {
                        win = false;
                        break;
                    }
                }
                if (win) return player;
            }

            if (i >= WIN_CONDITION - 1 && j <= SIZE - WIN_CONDITION) {
                bool win = true;
                for (size_t k = 0; k < WIN_CONDITION; k++) {
                    if (grid[i - k][j + k] != player) {
                        win = false;
                        break;
                    }
                }
                if (win) return player;
            }
        }
    }
    return Player::NONE;
}

bool Board::isBoardFull() const {
    return occupiedCells == SIZE * SIZE;
}
