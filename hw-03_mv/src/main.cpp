#include "GameController.h"
#include "Board.h"
#include "StdioBoardView.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    bool silent = false;
    
    if (argc == 2 && std::string(argv[1]) == "silent") {
        silent = true;
    }

    Board board;

    StdioBoardView view(board, silent);

    GameController game(board, view);

    game.startGame();
    
    return 0;
}
