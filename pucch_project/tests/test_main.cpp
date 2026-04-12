#include <iostream>

void test_qpsk();
void test_encoder();
void test_decoder();
void test_channel();
void test_simulation();

int main()
{
    std::cout << "=== RUN ALL TESTS ===\n\n";

    test_qpsk();
    std::cout << "\n";

    test_encoder();
    std::cout << "\n";

    test_decoder();
    std::cout << "\n";

    test_channel();
    std::cout << "\n";

    test_simulation();
    std::cout << "\n";

    return 0;
}