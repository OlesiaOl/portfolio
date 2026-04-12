#pragma once

#include <vector>

std::vector<int> encode_pucch( const std::vector<int>& bits, int num_bits );

void test_encoder();