#include "encoder.h"
#include "decoder.h"
#include "qpsk.h"
#include "channel.h"

#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>

#include "json.hpp"

using json = nlohmann::json;

struct SimulationResult
{
    double bler;
    int success;
    int failed;
};

static bool valid_num_bits(int num_bits)
{
    return num_bits == 2 || num_bits == 4 || num_bits == 6 ||
           num_bits == 8 || num_bits == 11;
}

static bool equal_bits(const std::vector<int>& a, const std::vector<int>& b)
{
    if (a.size() != b.size())
    {
        return false;
    }

    for (size_t i = 0; i < a.size(); i++)
    {
        if (a[i] != b[i])
        {
            return false;
        }
    }

    return true;
}

static bool parse_bits_array(const json& j, std::vector<int>& bits)
{
    if (!j.is_array())
    {
        return false;
    }

    bits.clear();

    for (size_t i = 0; i < j.size(); i++)
    {
        if (!j[i].is_number_integer())
        {
            return false;
        }

        int bit = j[i].get<int>();

        if (bit != 0 && bit != 1)
        {
            return false;
        }

        bits.push_back(bit);
    }

    return true;
}

static std::string complex_to_string(const Complex& c)
{
    std::ostringstream out;
    out << c.re;

    if (c.im >= 0.0)
    {
        out << "+";
    }

    out << c.im << "j";

    return out.str();
}

static bool parse_complex_string(const std::string& s, Complex& value)
{
    if (s.empty())
    {
        return false;
    }

    if (s.back() != 'j')
    {
        return false;
    }

    std::string body = s.substr(0, s.size() - 1);

    size_t split_pos = std::string::npos;

    for (size_t i = 1; i < body.size(); i++)
    {
        if (body[i] == '+' || body[i] == '-')
        {
            split_pos = i;
        }
    }

    if (split_pos == std::string::npos)
    {
        return false;
    }

    std::string re_part = body.substr(0, split_pos);
    std::string im_part = body.substr(split_pos);

    std::istringstream re_stream(re_part);
    std::istringstream im_stream(im_part);

    double re = 0.0;
    double im = 0.0;

    re_stream >> re;
    im_stream >> im;

    if (re_stream.fail() || !re_stream.eof())
    {
        return false;
    }

    if (im_stream.fail() || !im_stream.eof())
    {
        return false;
    }

    value.re = re;
    value.im = im;

    return true;
}

static bool parse_symbols_array(const json& j, std::vector<Complex>& symbols)
{
    if (!j.is_array())
    {
        return false;
    }

    symbols.clear();

    for (size_t i = 0; i < j.size(); i++)
    {
        if (!j[i].is_string())
        {
            return false;
        }

        Complex c;
        std::string s = j[i].get<std::string>();

        if (!parse_complex_string(s, c))
        {
            return false;
        }

        symbols.push_back(c);
    }

    return true;
}

static SimulationResult run_channel_simulation(int num_bits, double sigma, int iterations)
{
    std::mt19937 gen(12345);
    std::uniform_int_distribution<int> bit_dist(0, 1);

    int success = 0;
    int failed = 0;

    for (int it = 0; it < iterations; it++)
    {
        std::vector<int> bits(num_bits);

        for (int i = 0; i < num_bits; i++)
        {
            bits[i] = bit_dist(gen);
        }

        std::vector<int> codeword = encode_pucch(bits, num_bits);

        if (codeword.size() != 20)
        {
            SimulationResult error_result;
            error_result.bler = 1.0;
            error_result.success = 0;
            error_result.failed = iterations;
            return error_result;
        }

        std::vector<Complex> symbols = qpsk_modulate(codeword);

        if (symbols.size() != 10)
        {
            SimulationResult error_result;
            error_result.bler = 1.0;
            error_result.success = 0;
            error_result.failed = iterations;
            return error_result;
        }

        add_awgn_noise(symbols, sigma);

        std::vector<double> llr = qpsk_demodulate(symbols);
        std::vector<int> decoded = decode_pucch(llr, num_bits);

        if (equal_bits(bits, decoded))
        {
            success++;
        }
        else
        {
            failed++;
        }
    }

    SimulationResult result;
    result.success = success;
    result.failed = failed;
    result.bler = static_cast<double>(failed) / iterations;

    return result;
}

int main()
{
    std::ifstream input_file("input.json");

    if (!input_file.is_open())
    {
        std::cerr << "Error: cannot open input.json\n";
        return 1;
    }

    json input_json;

    try
    {
        input_file >> input_json;
    }
    catch (const std::exception&)
    {
        std::cerr << "Error: invalid json format\n";
        return 1;
    }

    if (!input_json.contains("mode") || !input_json["mode"].is_string())
    {
        std::cerr << "Error: missing or invalid field 'mode'\n";
        return 1;
    }

    std::string mode = input_json["mode"].get<std::string>();

    json result_json;
    result_json["mode"] = mode;

    if (mode == "coding")
    {
        if (!input_json.contains("num_of_pucch_f2_bits") ||
            !input_json["num_of_pucch_f2_bits"].is_number_integer())
        {
            std::cerr << "Error: missing or invalid field 'num_of_pucch_f2_bits'\n";
            return 1;
        }

        if (!input_json.contains("pucch_f2_bits"))
        {
            std::cerr << "Error: missing field 'pucch_f2_bits'\n";
            return 1;
        }

        int num_bits = input_json["num_of_pucch_f2_bits"].get<int>();

        if (!valid_num_bits(num_bits))
        {
            std::cerr << "Error: invalid num_of_pucch_f2_bits\n";
            return 1;
        }

        std::vector<int> bits;

        if (!parse_bits_array(input_json["pucch_f2_bits"], bits))
        {
            std::cerr << "Error: invalid field 'pucch_f2_bits'\n";
            return 1;
        }

        if (static_cast<int>(bits.size()) != num_bits)
        {
            std::cerr << "Error: bits size does not match num_of_pucch_f2_bits\n";
            return 1;
        }

        std::vector<int> codeword = encode_pucch(bits, num_bits);

        if (codeword.size() != 20)
        {
            std::cerr << "Error: encoder failed\n";
            return 1;
        }

        std::vector<Complex> symbols = qpsk_modulate(codeword);

        if (symbols.size() != 10)
        {
            std::cerr << "Error: qpsk modulation failed\n";
            return 1;
        }

        json symbols_json = json::array();

        for (size_t i = 0; i < symbols.size(); i++)
        {
            symbols_json.push_back(complex_to_string(symbols[i]));
        }

        result_json["qpsk_symbols"] = symbols_json;
    }
    else if (mode == "decoding")
    {
        if (!input_json.contains("num_of_pucch_f2_bits") ||
            !input_json["num_of_pucch_f2_bits"].is_number_integer())
        {
            std::cerr << "Error: missing or invalid field 'num_of_pucch_f2_bits'\n";
            return 1;
        }

        if (!input_json.contains("qpsk_symbols"))
        {
            std::cerr << "Error: missing field 'qpsk_symbols'\n";
            return 1;
        }

        int num_bits = input_json["num_of_pucch_f2_bits"].get<int>();

        if (!valid_num_bits(num_bits))
        {
            std::cerr << "Error: invalid num_of_pucch_f2_bits\n";
            return 1;
        }

        std::vector<Complex> symbols;

        if (!parse_symbols_array(input_json["qpsk_symbols"], symbols))
        {
            std::cerr << "Error: invalid field 'qpsk_symbols'\n";
            return 1;
        }

        if (symbols.size() != 10)
        {
            std::cerr << "Error: qpsk_symbols size must be 10\n";
            return 1;
        }

        std::vector<double> llr = qpsk_demodulate(symbols);
        std::vector<int> bits = decode_pucch(llr, num_bits);

        if (static_cast<int>(bits.size()) != num_bits)
        {
            std::cerr << "Error: decoder failed\n";
            return 1;
        }

        result_json["num_of_pucch_f2_bits"] = num_bits;
        result_json["pucch_f2_bits"] = bits;
    }
    else if (mode == "channel simulation")
    {
        if (!input_json.contains("num_of_pucch_f2_bits") ||
            !input_json["num_of_pucch_f2_bits"].is_number_integer())
        {
            std::cerr << "Error: missing or invalid field 'num_of_pucch_f2_bits'\n";
            return 1;
        }

        if (!input_json.contains("noise") ||
            !(input_json["noise"].is_number_float() || input_json["noise"].is_number_integer()))
        {
            std::cerr << "Error: missing or invalid field 'noise'\n";
            return 1;
        }

        if (!input_json.contains("iterations") ||
            !input_json["iterations"].is_number_integer())
        {
            std::cerr << "Error: missing or invalid field 'iterations'\n";
            return 1;
        }

        int num_bits = input_json["num_of_pucch_f2_bits"].get<int>();
        double noise = input_json["noise"].get<double>();
        int iterations = input_json["iterations"].get<int>();

        if (!valid_num_bits(num_bits))
        {
            std::cerr << "Error: invalid num_of_pucch_f2_bits\n";
            return 1;
        }

        if (noise < 0.0)
        {
            std::cerr << "Error: noise must be non-negative\n";
            return 1;
        }

        if (iterations <= 0)
        {
            std::cerr << "Error: iterations must be positive\n";
            return 1;
        }

        SimulationResult sim = run_channel_simulation(num_bits, noise, iterations);

        result_json["num_of_pucch_f2_bits"] = num_bits;
        result_json["bler"] = sim.bler;
        result_json["success"] = sim.success;
        result_json["failed"] = sim.failed;
    }
    else
    {
        std::cerr << "Error: unknown mode\n";
        return 1;
    }

    std::ofstream output_file("result.json");

    if (!output_file.is_open())
    {
        std::cerr << "Error: cannot open result.json for writing\n";
        return 1;
    }

    output_file << result_json.dump(4) << "\n";

    return 0;
}