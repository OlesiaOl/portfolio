#include "simulation.h"

#include <iostream>

void test_simulation() {
    std::cout << "=== SIMULATION TEST ===\n";

    int num_bits = 4;
    int iterations = 100;

    double bler0 = simulate_bler(num_bits, 0.0, iterations);

    std::cout << "BLER sigma=0 : " << bler0 << "\n";

    if (bler0 == 0.0)
    {
        std::cout << "PASS\n";
    }
    else
    {
        std::cout << "FAIL\n";
    }
}