#include "encoder.h"

#include <iostream>
#include <vector>

static bool vectors_equal(const std::vector<int>& a, const std::vector<int>& b)
{
    if (a.size() != b.size())
    {
        return false;
    }

    for (size_t i = 0; i < a.size(); i++)
    {
        if (a[i] != b[i])
        {
            return false;
        }
    }

    return true;
}

static bool is_binary_vector(const std::vector<int>& v)
{
    for (size_t i = 0; i < v.size(); i++)
    {
        if (v[i] != 0 && v[i] != 1)
        {
            return false;
        }
    }

    return true;
}

static bool test_encoder_size_4_bits()
{
    std::cout << "[TEST] encoder size for 4 bits\n";

    std::vector<int> bits = {1, 0, 1, 1};
    std::vector<int> codeword = encode_pucch(bits, 4);

    if (codeword.size() != 20)
    {
        std::cout << "  FAIL: codeword size is not 20\n";
        return false;
    }

    std::cout << "  PASS\n";
    return true;
}

static bool test_encoder_binary_output()
{
    std::cout << "[TEST] encoder output is binary\n";

    std::vector<int> bits = {1, 0, 1, 1};
    std::vector<int> codeword = encode_pucch(bits, 4);

    if (!is_binary_vector(codeword))
    {
        std::cout << "  FAIL: codeword contains non-binary values\n";
        return false;
    }

    std::cout << "  PASS\n";
    return true;
}

static bool test_encoder_repeatability()
{
    std::cout << "[TEST] encoder repeatability\n";

    std::vector<int> bits = {1, 0, 1, 1, 0, 1};
    std::vector<int> codeword1 = encode_pucch(bits, 6);
    std::vector<int> codeword2 = encode_pucch(bits, 6);

    if (!vectors_equal(codeword1, codeword2))
    {
        std::cout << "  FAIL: same input gives different outputs\n";
        return false;
    }

    std::cout << "  PASS\n";
    return true;
}

static bool test_encoder_invalid_num_bits()
{
    std::cout << "[TEST] encoder invalid num_bits\n";

    std::vector<int> bits = {1, 0, 1, 1};
    std::vector<int> codeword = encode_pucch(bits, 5);

    if (!codeword.empty())
    {
        std::cout << "  FAIL: expected empty result\n";
        return false;
    }

    std::cout << "  PASS\n";
    return true;
}

static bool test_encoder_invalid_size()
{
    std::cout << "[TEST] encoder invalid bits.size()\n";

    std::vector<int> bits = {1, 0, 1};
    std::vector<int> codeword = encode_pucch(bits, 4);

    if (!codeword.empty())
    {
        std::cout << "  FAIL: expected empty result\n";
        return false;
    }

    std::cout << "  PASS\n";
    return true;
}

static bool test_encoder_invalid_bit_value()
{
    std::cout << "[TEST] encoder invalid bit value\n";

    std::vector<int> bits = {1, 0, 2, 1};
    std::vector<int> codeword = encode_pucch(bits, 4);

    if (!codeword.empty())
    {
        std::cout << "  FAIL: expected empty result\n";
        return false;
    }

    std::cout << "  PASS\n";
    return true;
}

static bool test_encoder_all_valid_lengths()
{
    std::cout << "[TEST] encoder all valid lengths\n";

    std::vector<int> bits2 = {1, 0};
    std::vector<int> bits4 = {1, 0, 1, 1};
    std::vector<int> bits6 = {1, 0, 1, 1, 0, 1};
    std::vector<int> bits8 = {1, 0, 1, 1, 0, 1, 0, 0};
    std::vector<int> bits11 = {1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0};

    std::vector<int> c2 = encode_pucch(bits2, 2);
    std::vector<int> c4 = encode_pucch(bits4, 4);
    std::vector<int> c6 = encode_pucch(bits6, 6);
    std::vector<int> c8 = encode_pucch(bits8, 8);
    std::vector<int> c11 = encode_pucch(bits11, 11);

    bool ok = true;

    if (c2.size() != 20)
    {
        ok = false;
    }

    if (c4.size() != 20)
    {
        ok = false;
    }

    if (c6.size() != 20)
    {
        ok = false;
    }

    if (c8.size() != 20)
    {
        ok = false;
    }

    if (c11.size() != 20)
    {
        ok = false;
    }

    if (!ok)
    {
        std::cout << "  FAIL: one of valid lengths did not produce 20 bits\n";
        return false;
    }

    std::cout << "  PASS\n";
    return true;
}

void test_encoder()
{
    int passed = 0;
    int total = 7;

    if (test_encoder_size_4_bits())
    {
        passed++;
    }

    if (test_encoder_binary_output())
    {
        passed++;
    }

    if (test_encoder_repeatability())
    {
        passed++;
    }

    if (test_encoder_invalid_num_bits())
    {
        passed++;
    }

    if (test_encoder_invalid_size())
    {
        passed++;
    }

    if (test_encoder_invalid_bit_value())
    {
        passed++;
    }

    if (test_encoder_all_valid_lengths())
    {
        passed++;
    }

    std::cout << "\n=== ENCODER RESULT ===\n";
    std::cout << "Passed: " << passed << " / " << total << "\n";

    if (passed == total)
    {
        std::cout << "ALL ENCODER TESTS PASSED\n";
    }
    else
    {
        std::cout << "SOME ENCODER TESTS FAILED\n";
    }
}