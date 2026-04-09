#ifndef BOARD_TEST_H
#define BOARD_TEST_H

#include "Tests.h"
#include "Board.h"
#include <string>

class BoardTest : public Test {
public:
    void runAllTests() override {
        testBoardInitialization();
        testValidMove();
        testInvalidMove();
        testWinByRow();
        testWinByColumn();
        testWinByMainDiagonal();
        testWinByAntiDiagonal();
        testNoWinYet();
        testMoveOutOfBounds();
        testBoardReset();
        testAlternatingPattern();
        testInvalidInput();
        testWinningMove();
        testDrawMove();
        testResetFunction();
    }

private:
    void checkTest(bool condition, const std::string& testName);
    void testAlternatingPattern();
    void testBoardInitialization();
    void testValidMove();
    void testInvalidMove();
    void testWinByRow();
    void testWinByColumn();
    void testWinByMainDiagonal();
    void testWinByAntiDiagonal();
    void testNoWinYet();
    void testMoveOutOfBounds();
    void testBoardReset();
    void testInvalidInput();
    void testWinningMove();
    void testDrawMove();
    void testResetFunction();
};

#endif // BOARD_TEST_H
