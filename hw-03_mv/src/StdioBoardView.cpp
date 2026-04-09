#include "StdioBoardView.h"
#include "Board.h"
#include <iostream>
#include <sstream>

StdioBoardView::StdioBoardView(Board &b, bool silent) : board(b), silent(silent) {}

void StdioBoardView::runGame() {
    GameState gameState = GameState::IN_PROGRESS;
    Player MeowPlayer = Player::NOUGHT;

    if (!silent) {
        updateBoard();
    }

    while (gameState == GameState::IN_PROGRESS) {
        getPlayerMove(MeowPlayer);

        Player winner = board.checkWin();
        if (winner != Player::NONE) {
            gameState = (winner == Player::CROSS) ? GameState::X_WINS : GameState::O_WINS;
        } else if (board.isBoardFull()) {
            gameState = GameState::DRAW;
        }

        if (!silent) {
            updateBoard();
        }

        if (gameState == GameState::IN_PROGRESS) {
            MeowPlayer = (MeowPlayer == Player::CROSS) ? Player::NOUGHT : Player::CROSS;
        }
    }

    showGameState(gameState);
}

void StdioBoardView::showBoard() const {
    if (silent) return;
    std::cout << "\n";
    for (size_t i = 0; i < SIZE; i++) {
        for (size_t j = 0; j < SIZE; j++) {
            if (board.getGrid()[i][j] == Player::NOUGHT) {
                std::cout << "O";
            } else if (board.getGrid()[i][j] == Player::CROSS) {
                std::cout << "X";
            } else {
                std::cout << ".";
            }
        }
        std::cout << "\n";
    }
}

void StdioBoardView::updateBoard() {
    if (!silent) {
        showBoard();
    }
}

void StdioBoardView::showGameState(GameState state) const {
    if (state == GameState::IN_PROGRESS) {
        std::cout << "The game is in progress.\n";
    } else if (state == GameState::X_WINS) {
        std::cout << "X wins!\n";
        exit(0);
    } else if (state == GameState::O_WINS) {
        std::cout << "O wins!\n";
        exit(0);
    } else {
        std::cout << "Draw.\n";
        exit(0);
    }
    std::cout << "\n";
}

void StdioBoardView::getPlayerMove(Player player) {
    std::string input;
    int x, y;

    std::cout << (player == Player::CROSS ? "X" : "O") << " move: ";
    std::getline(std::cin, input);

    std::istringstream moveStream(input);
    if (!(moveStream >> x >> y)) {
        std::cout << "Bad move!\n";
        getPlayerMove(player);
    }

    if (x == -1 && y == -1) {
        exit(0);
    } else if (x >= 0 && y >= 0 && x < SIZE && y < SIZE && board.move(x, y, player)) {
        board.move(x, y, player);
    } else {
        std::cout << "Bad move!\n";
        getPlayerMove(player);
    }
}
