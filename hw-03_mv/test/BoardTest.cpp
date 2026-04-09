#include "BoardTest.h"
#include "Board.h"

#include <sstream>
#include <string>
#include <iostream>
#include <cstddef>

void BoardTest::checkTest(bool condition, const std::string& testName) {
    if (!condition) {
        std::cerr << "Test failed: " << testName << std::endl;
        failedNum++;
    }
    totalNum++;
}

void BoardTest::testBoardInitialization() {
    Board board;
    bool isEmpty = true;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board.getGrid()[i][j] != Player::NONE) {
                isEmpty = false;
            }
        }
    }
    checkTest(isEmpty, "Board Initialization Test");
    checkTest(board.getState() == GameState::IN_PROGRESS, "Initial State Test");
}

void BoardTest::testValidMove() {
    Board board;
    board.move(1, 1, Player::CROSS);
    checkTest(board.getGrid()[1][1] == Player::CROSS, "Move Execution Test");
}

void BoardTest::testInvalidMove() {
    Board board;
    board.move(0, 0, Player::NOUGHT);
    bool moveResult = board.move(0, 0, Player::CROSS);
    checkTest(!moveResult, "Invalid Move Check");
    checkTest(board.getGrid()[0][0] == Player::NOUGHT, "Invalid Move Execution Test");
}

void BoardTest::testWinByRow() {
    Board board;
    for (int j = 0; j < WIN_CONDITION; ++j) {
        board.move(0, j, Player::CROSS);
    }
    checkTest(board.getState() == GameState::X_WINS, "Win by Row Test");
}

void BoardTest::testWinByColumn() {
    Board board;
    for (int i = 0; i < WIN_CONDITION; ++i) {
        board.move(i, 1, Player::NOUGHT);
    }
    checkTest(board.getState() == GameState::O_WINS, "Win by Column Test");
}

void BoardTest::testWinByMainDiagonal() {
    Board board;
    for (int i = 0; i < WIN_CONDITION; ++i) {
        board.move(i, i, Player::CROSS);
    }
    checkTest(board.getState() == GameState::X_WINS, "Win by Main Diagonal Test");
}

void BoardTest::testWinByAntiDiagonal() {
    Board board;
    for (int i = 0; i < WIN_CONDITION; ++i) {
        board.move(i, WIN_CONDITION - 1 - i, Player::NOUGHT);
    }
    checkTest(board.getState() == GameState::O_WINS, "Win by Anti-Diagonal Test");
}

void BoardTest::testNoWinYet() {
    Board board;
    board.move(0, 0, Player::CROSS);
    board.move(0, 1, Player::CROSS);
    checkTest(board.getState() == GameState::IN_PROGRESS, "No Win Yet Test");
}

void BoardTest::testMoveOutOfBounds() {
    Board board;
    bool moveNegative = board.move(-1, 0, Player::CROSS);
    bool moveOverflow = board.move(SIZE, SIZE, Player::NOUGHT);
    checkTest(!moveNegative, "testMoveOutOfBounds (negative indices)");
    checkTest(!moveOverflow, "testMoveOutOfBounds (overflow indices)");
}

void BoardTest::testBoardReset() {
    Board board;
    board.move(0, 0, Player::CROSS);
    board.reset();
    checkTest(board.getGrid()[0][0] == Player::NONE, "Board Reset Test");
    checkTest(board.getState() == GameState::IN_PROGRESS, "Board State Reset Test");
}

void BoardTest::testAlternatingPattern() {
    Board board;
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if ((i % 2 == 0 && j % 4 < 2) || (i % 2 == 1 && j % 4 >= 2)) {
                board.move(i, j, Player::NOUGHT);
            } else {
                board.move(i, j, Player::CROSS);
            }
        }
    }
    checkTest(board.getState() == GameState::DRAW, "Alternating Pattern Test");
}

void BoardTest::testInvalidInput() {
    Board board;

    bool result = board.move('a', 0, Player::CROSS);
    checkTest(!result, "Invalid Input (letter)");

    result = board.move(100, 100, Player::NOUGHT);
    checkTest(!result, "Invalid Input (too large)");

    result = board.move(1, -1, Player::CROSS);
    checkTest(!result, "Invalid Input (negative number)");
}

void BoardTest::testWinningMove() {
    Board board;

    board.move(0, 0, Player::CROSS);
    board.move(1, 0, Player::CROSS);
    board.move(2, 0, Player::CROSS);
    board.move(3, 0, Player::CROSS);
    board.move(4, 0, Player::CROSS);
    checkTest(board.getState() == GameState::X_WINS, "Test: X wins vertically");
}

void BoardTest::testDrawMove() {
    Board board;
    std::string firstLine = "0001110001";
    std::string secondLine = "1110001110";

    for (int i = 0; i < 10; ++i) {
        std::string currentLine = (i % 2 == 0) ? firstLine : secondLine;

        for (int j = 0; j < 10; ++j) {
            Player player = (currentLine[j] == '0') ? Player::NOUGHT : Player::CROSS;
            board.move(i, j, player);
        }
    }
    Player winner = board.checkWin();
    if (winner != Player::NONE) {
        std::cerr << "Test failed: Winner found unexpectedly." << std::endl;
        return;
    }

    bool isBoardFull = board.isBoardFull();
    checkTest(isBoardFull && board.getState() == GameState::DRAW, "Test: Draw");
}

void BoardTest::testResetFunction() {
    Board board;
    board.reset();
    std::stringstream ss;

    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            Player cell = board.getGrid()[i][j];
            if (cell != Player::NONE) {
                ss << "Cell (" << i << "," << j << ") should be NONE after reset\n";
            }
        }
    }
    checkTest(board.getState() == GameState::IN_PROGRESS, "Game state should be IN_PROGRESS after reset");
}
