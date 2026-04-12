#include "channel.h"

#include <iostream>
#include <random>
#include <vector>

void add_awgn_noise(std::vector<Complex>& symbols, double sigma)
{
    if (sigma < 0.0)
    {
        std::cerr << "Channel error: sigma must be non-negative\n";
        return;
    }

    static std::random_device rd;
    static std::mt19937 gen(rd());

    std::normal_distribution<double> dist(0.0, sigma);

    for (size_t i = 0; i < symbols.size(); i++)
    {
        symbols[i].re += dist(gen);
        symbols[i].im += dist(gen);
    }
}