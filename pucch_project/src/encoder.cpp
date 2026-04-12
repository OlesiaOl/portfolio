#include "encoder.h"

#include <iostream>
#include <vector>

static const int M[20][13] = {
    {1,1,0,0,0,0,0,0,0,0,1,1,0},
    {1,1,1,0,0,0,0,0,0,1,1,1,0},
    {1,0,0,1,0,0,1,0,1,1,1,1,1},
    {1,0,1,1,0,0,0,0,1,0,1,1,1},
    {1,1,1,1,0,0,0,1,0,0,1,1,1},
    {1,1,0,0,1,0,1,1,1,0,1,1,1},
    {1,0,1,0,1,0,1,0,1,1,1,1,1},
    {1,0,0,1,1,0,0,1,1,0,1,1,1},
    {1,1,0,1,1,0,0,1,0,1,1,1,1},
    {1,0,1,1,1,0,1,0,0,1,1,1,1},
    {1,0,1,0,0,1,1,1,0,1,1,1,1},
    {1,1,1,0,0,1,1,0,1,0,1,1,1},
    {1,0,0,1,0,1,0,1,1,1,1,1,1},
    {1,1,0,1,0,1,0,1,0,1,1,1,1},
    {1,0,0,0,1,1,0,1,0,0,1,0,1},
    {1,1,0,0,1,1,1,1,0,1,1,0,1},
    {1,1,1,0,1,1,1,0,0,1,0,1,1},
    {1,0,0,1,1,1,0,0,1,0,0,1,1},
    {1,1,0,1,1,1,1,1,0,0,0,0,0},
    {1,0,0,0,0,1,1,0,0,0,0,0,0}
};

static bool valid_num_bits(int num_bits) {
    bool res = (num_bits == 2 || num_bits == 4 || num_bits == 6 ||
           num_bits == 8 || num_bits == 11);
    return res;
}

std::vector<int> encode_pucch(const std::vector<int>& bits, int num_bits) {
    std::vector<int> res;

    if (valid_num_bits(num_bits) == 0) {
        std::cout << "Encoder error: invalid num_bits\n";
        return res;
    }

    if (static_cast<int>(bits.size()) != num_bits) {
        std::cout << "Encoder error: invald bits.size()\n";
        return res;
    }

    for (size_t i = 0; i < bits.size(); i++) {
        if (bits[i] != 0 && bits[i] != 1) {
            std::cout << "Encoder error: invalid bit \n";
            return res;
        }

    }

    res.resize(20,0);

    for (int i = 0; i < 20; i++) {
        int sum = 0;
        for (int j = 0; j < num_bits; j++) {
            sum = sum ^ (bits[j] & M[i][j]);
        }
        res[i] = sum;
    }

    return res;
}