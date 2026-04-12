#pragma once

#include <vector>

std::vector<int> decode_pucch(const std::vector<double>& llr, int num_bits);