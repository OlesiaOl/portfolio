#include "qpsk.h"

#include <iostream>
#include <vector>

std::vector<Complex> qpsk_modulate(const std::vector<int>& bits) {
    std::vector<Complex> symbols;

    if (bits.size() % 2 != 0) {
        std::cerr << "QPSK modulation error: number of bits must be even\n";
        return symbols;
    }

    symbols.reserve(bits.size() / 2);

    for (size_t i = 0; i < bits.size(); i += 2) {
        int bit1 = bits[i];
        int bit2 = bits[i + 1];

        Complex s;

        if (bit1 == 0)
        {
            s.re = -1.0;
        } else {
            s.re = 1.0;
        }

        if (bit2 == 0)
        {
            s.im = -1.0;
        } else {
            s.im = 1.0;
        }

        symbols.push_back(s);
    }

    return symbols;
}

std::vector<double> qpsk_demodulate(const std::vector<Complex>& symbols) {
    std::vector<double> soft_bits;
    soft_bits.reserve(symbols.size() * 2);

    for (size_t i = 0; i < symbols.size(); i++) {
        soft_bits.push_back(symbols[i].re);
        soft_bits.push_back(symbols[i].im);
    }

    return soft_bits;
}