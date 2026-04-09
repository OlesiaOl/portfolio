#include "Tests.h"
#include <cstddef>
#include <iostream>

int Test::failedNum = 0;
int Test::totalNum = 0;

bool Test::showFinalResult() {
    std::cout << "Total tests: " << totalNum <<" , Failed tests: " << failedNum << "\n";
    return failedNum == 0;
}
