#include "GameController.h"

GameController::GameController(Board& board, StdioBoardView& view) 
    : board(board), view(view) {}

void GameController::startGame() {
    board.reset();
    view.runGame();
}
