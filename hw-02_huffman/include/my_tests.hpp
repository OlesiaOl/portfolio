#ifndef MY_TESTS_HPP
#define MY_TESTS_HPP

#include <string>

class Test {
public:
    virtual void runAllTests() = 0;
    virtual ~Test() = default;

protected:
    void checkTest(bool condition, const std::string& testName);
};

void printFinalResults();

#endif // MY_TESTS_HPP
