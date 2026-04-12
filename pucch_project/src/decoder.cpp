#include "decoder.h"
#include "encoder.h"

#include <iostream>
#include <limits>
#include <vector>

static bool valid_num_bits(int num_bits) {
    return num_bits == 2 || num_bits == 4 ||
           num_bits == 6 || num_bits == 8 ||
           num_bits == 11;
}

std::vector<int> decode_pucch(const std::vector<double>& llr, int num_bits)
{
    std::vector<int> best_bits;

    if (!valid_num_bits(num_bits))
    {
        std::cerr << "Decoder error: invalid num_bits\n";
        return best_bits;
    }

    if (llr.size() != 20)
    {
        std::cerr << "Decoder error: llr size must be 20\n";
        return best_bits;
    }

    double best_metric = -std::numeric_limits<double>::infinity();

    int total = 1 << num_bits;

    for (int mask = 0; mask < total; mask++) {
        std::vector<int> candidate(num_bits);

        for (int j = 0; j < num_bits; j++) {
            candidate[j] = (mask >> (num_bits - 1 - j)) & 1;
        }

        std::vector<int> codeword = encode_pucch(candidate, num_bits);

        double metric = 0.0;

        for (int i = 0; i < 20; i++) {
            if (codeword[i] == 1) {
                metric += llr[i];
            } else {
                metric -= llr[i];
            }
        }

        if (metric > best_metric) {
            best_metric = metric;
            best_bits = candidate;
        }
    }

    return best_bits;
}