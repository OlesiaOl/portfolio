#include "my_tests.hpp"
#include <iostream>

static int passed = 0;
static int failed = 0;

void Test::checkTest(bool condition, const std::string& testName) {
    if (condition) {
        std::cout << "[PASS] " << testName << "\n";
        passed++;
    } else {
        std::cout << "[FAIL] " << testName << "\n";
        failed++;
    }
}

void printFinalResults() {
    std::cout << "\n=== Test Summary ===\n";
    std::cout << "Passed: " << passed << "\n";
    std::cout << "Failed: " << failed << "\n";
}
