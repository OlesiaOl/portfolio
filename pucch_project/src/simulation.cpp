#include "simulation.h"

#include "encoder.h"
#include "decoder.h"
#include "qpsk.h"
#include "channel.h"

#include <random>
#include <vector>

static bool equal_bits(const std::vector<int>& a, const std::vector<int>& b) {
    if (a.size() != b.size()) {
        return false;
    }

    for (size_t i = 0; i < a.size(); i++) {
        if (a[i] != b[i]) {
            return false;
        }
    }

    return true;
}

double simulate_bler(int num_bits, double sigma, int iterations) {
    std::mt19937 gen(12345);
    std::uniform_int_distribution<int> bit_dist(0, 1);

    int errors = 0;

    for (int it = 0; it < iterations; it++){
        std::vector<int> bits(num_bits);

        for (int i = 0; i < num_bits; i++){
            bits[i] = bit_dist(gen);
        }

        auto codeword = encode_pucch(bits, num_bits);

        auto symbols = qpsk_modulate(codeword);

        add_awgn_noise(symbols, sigma);

        auto llr = qpsk_demodulate(symbols);

        auto decoded = decode_pucch(llr, num_bits);

        if (!equal_bits(bits, decoded)){
            errors++;
        }
    }

    double bler = static_cast<double>(errors) / iterations;

    return bler;
}