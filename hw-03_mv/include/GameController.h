#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include "Board.h"
#include "StdioBoardView.h"

class GameController {
private:
    Board& board;
    StdioBoardView& view;

public:
    GameController(Board& board, StdioBoardView& view);
    
    void startGame();
};

#endif // GAMECONTROLLER_H