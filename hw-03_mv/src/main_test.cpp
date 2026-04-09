#include "BoardTest.h"

int main() {
    BoardTest boardTest;
    boardTest.runAllTests();
    
    return Test::showFinalResult() ? 0 : 1;
}
