#pragma once

#include <vector>

struct Complex
{
    double re;
    double im;
};

std::vector<Complex> qpsk_modulate(const std::vector<int>& bits);
std::vector<double> qpsk_demodulate(const std::vector<Complex>& symbols);

void test_qpsk();