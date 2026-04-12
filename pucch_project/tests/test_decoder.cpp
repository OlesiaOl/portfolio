#include "decoder.h"
#include "encoder.h"
#include "qpsk.h"

#include <iostream>

static bool equal(const std::vector<int>& a, const std::vector<int>& b) {
    if (a.size() != b.size()) return false;

    for (size_t i = 0; i < a.size(); i++)
        if (a[i] != b[i]) return false;

    return true;
}

void test_decoder() {
    std::cout << "=== TEST DECODER ===\n";

    std::vector<int> bits = {1,0,1,1};

    auto codeword = encode_pucch(bits,4);
    auto symbols = qpsk_modulate(codeword);
    auto llr = qpsk_demodulate(symbols);

    auto decoded = decode_pucch(llr,4);

    if (equal(bits, decoded))
        std::cout << "PASS\n";
    else
        std::cout << "FAIL\n";
}