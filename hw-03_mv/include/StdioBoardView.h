#ifndef STDIOBOARDVIEW_H
#define STDIOBOARDVIEW_H

#include "Board.h"

class StdioBoardView {
private:
    Board &board;
    bool silent;
public:
    explicit StdioBoardView(Board &b, bool silent = false);
    void runGame();
    void showBoard() const;
    void updateBoard();
    void showGameState(GameState state) const;
    void getPlayerMove(Player player);
};

#endif // STDIOBOARDVIEW_H
