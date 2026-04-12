#include "qpsk.h"

#include <iostream>
#include <vector>

static bool check_equal_double(double a, double b)
{
    double eps = 1e-9;

    if (a - b < 0)
    {
        return b - a < eps;
    }

    return a - b < eps;
}

static bool test_modulation_basic()
{
    std::cout << "[TEST] QPSK modulation basic\n";

    std::vector<int> bits = {0, 0, 0, 1, 1, 0, 1, 1};
    std::vector<Complex> symbols = qpsk_modulate(bits);

    if (symbols.size() != 4)
    {
        std::cout << "  FAIL: wrong number of symbols\n";
        return false;
    }

    bool ok = true;

    if (!(check_equal_double(symbols[0].re, -1.0) && check_equal_double(symbols[0].im, -1.0)))
    {
        ok = false;
    }

    if (!(check_equal_double(symbols[1].re, -1.0) && check_equal_double(symbols[1].im, 1.0)))
    {
        ok = false;
    }

    if (!(check_equal_double(symbols[2].re, 1.0) && check_equal_double(symbols[2].im, -1.0)))
    {
        ok = false;
    }

    if (!(check_equal_double(symbols[3].re, 1.0) && check_equal_double(symbols[3].im, 1.0)))
    {
        ok = false;
    }

    if (ok)
    {
        std::cout << "  PASS\n";
    }
    else
    {
        std::cout << "  FAIL: wrong mapping\n";
    }

    return ok;
}

static bool test_demodulation_basic()
{
    std::cout << "[TEST] QPSK demodulation basic\n";

    std::vector<Complex> symbols = {
        {-1.0, -1.0},
        {-1.0, 1.0},
        {1.0, -1.0},
        {1.0, 1.0}
    };

    std::vector<double> soft = qpsk_demodulate(symbols);

    if (soft.size() != 8)
    {
        std::cout << "  FAIL: wrong number of soft bits\n";
        return false;
    }

    std::vector<double> expected = {
        -1.0, -1.0,
        -1.0, 1.0,
        1.0, -1.0,
        1.0, 1.0
    };

    bool ok = true;

    for (size_t i = 0; i < soft.size(); i++)
    {
        if (!check_equal_double(soft[i], expected[i]))
        {
            ok = false;
        }
    }

    if (ok)
    {
        std::cout << "  PASS\n";
    }
    else
    {
        std::cout << "  FAIL: wrong LLR values\n";
    }

    return ok;
}

static bool test_full_chain_without_noise()
{
    std::cout << "[TEST] Full chain without noise\n";

    std::vector<int> bits = {0, 0, 1, 1, 0, 1, 1, 0};

    std::vector<Complex> symbols = qpsk_modulate(bits);
    std::vector<double> soft = qpsk_demodulate(symbols);

    if (soft.size() != bits.size())
    {
        std::cout << "  FAIL: soft bits size != input bits size\n";
        return false;
    }

    bool ok = true;

    for (size_t i = 0; i < bits.size(); i++)
    {
        int hard_bit;

        if (soft[i] > 0.0)
        {
            hard_bit = 1;
        }
        else
        {
            hard_bit = 0;
        }

        if (hard_bit != bits[i])
        {
            ok = false;
            std::cout << "  FAIL: mismatch at index " << i
                      << ", expected " << bits[i]
                      << ", got " << hard_bit << "\n";
        }
    }

    if (ok)
    {
        std::cout << "  PASS\n";
    }

    return ok;
}

static bool test_odd_number_of_bits()
{
    std::cout << "[TEST] Odd number of bits\n";

    std::vector<int> bits = {1, 0, 1};
    std::vector<Complex> symbols = qpsk_modulate(bits);

    if (!symbols.empty())
    {
        std::cout << "  FAIL: expected empty result for odd number of bits\n";
        return false;
    }

    std::cout << "  PASS\n";
    return true;
}

void test_qpsk()
{
    int passed = 0;
    int total = 4;

    if (test_modulation_basic())
    {
        passed++;
    }

    if (test_demodulation_basic())
    {
        passed++;
    }

    if (test_full_chain_without_noise())
    {
        passed++;
    }

    if (test_odd_number_of_bits())
    {
        passed++;
    }

    std::cout << "\n=== RESULT ===\n";
    std::cout << "Passed: " << passed << " / " << total << "\n";

    if (passed == total)
    {
        std::cout << "ALL TESTS PASSED\n";
    }
    else
    {
        std::cout << "SOME TESTS FAILED\n";
    }
}