#include "channel.h"
#include "qpsk.h"

#include <iostream>
#include <vector>

static bool equal_double(double a, double b)
{
    double eps = 1e-9;

    if (a > b)
    {
        return (a - b) < eps;
    }

    return (b - a) < eps;
}

static bool equal_symbols(const std::vector<Complex>& a, const std::vector<Complex>& b)
{
    if (a.size() != b.size())
    {
        return false;
    }

    for (size_t i = 0; i < a.size(); i++)
    {
        if (!equal_double(a[i].re, b[i].re))
        {
            return false;
        }

        if (!equal_double(a[i].im, b[i].im))
        {
            return false;
        }
    }

    return true;
}

static bool test_channel_sigma_zero()
{
    std::cout << "[TEST] channel sigma = 0\n";

    std::vector<Complex> symbols = {
        {1.0, -1.0},
        {-1.0, 1.0},
        {1.0, 1.0}
    };

    std::vector<Complex> original = symbols;

    add_awgn_noise(symbols, 0.0);

    if (!equal_symbols(symbols, original))
    {
        std::cout << "  FAIL: symbols changed when sigma = 0\n";
        return false;
    }

    std::cout << "  PASS\n";
    return true;
}

static bool test_channel_size_preserved()
{
    std::cout << "[TEST] channel size preserved\n";

    std::vector<Complex> symbols = {
        {1.0, -1.0},
        {-1.0, 1.0},
        {1.0, 1.0},
        {-1.0, -1.0}
    };

    size_t old_size = symbols.size();

    add_awgn_noise(symbols, 0.5);

    if (symbols.size() != old_size)
    {
        std::cout << "  FAIL: size changed\n";
        return false;
    }

    std::cout << "  PASS\n";
    return true;
}

void test_channel()
{
    int passed = 0;
    int total = 2;

    if (test_channel_sigma_zero())
    {
        passed++;
    }

    if (test_channel_size_preserved())
    {
        passed++;
    }

    std::cout << "\n=== CHANNEL RESULT ===\n";
    std::cout << "Passed: " << passed << " / " << total << "\n";

    if (passed == total)
    {
        std::cout << "ALL CHANNEL TESTS PASSED\n";
    }
    else
    {
        std::cout << "SOME CHANNEL TESTS FAILED\n";
    }
}