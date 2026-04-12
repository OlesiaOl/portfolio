#pragma once

#include <vector>
#include "qpsk.h"

void add_awgn_noise(std::vector<Complex>& symbols, double sigma);