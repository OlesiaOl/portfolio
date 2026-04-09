#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>

#include "huffman_archiver.hpp"

int main(int argc, char* argv[]) {
    bool compress = false;
    bool decompress = false;
    std::string input_file;
    std::string output_file;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        if (arg == "-c") {
            compress = true;
        } else if (arg == "-u") {
            decompress = true;
        } else if (arg == "-f" || arg == "--file") {
            if (i + 1 < argc) {
                input_file = argv[++i];
            }
        } else if (arg == "-o" || arg == "--output") {
            if (i + 1 < argc) {
                output_file = argv[++i];
            }
        }
    }

    if (input_file.empty() || output_file.empty() || (compress == decompress)) {
        return 1;
    }

    std::ifstream in(input_file, std::ios::binary);
    std::ofstream out(output_file, std::ios::binary);

    if (!in.is_open() || !out.is_open()) {
        return 1;
    }

    HuffmanArchiver archiver;

    if (compress) {
        archiver.encode(in, out);
        std::cout << archiver.get_original_size() << "\n";
        std::cout << archiver.get_compressed_data_size() << "\n";
        std::cout << archiver.get_metadata_size() << "\n";
    } else {
        archiver.decode(in, out);
        std::cout << archiver.get_compressed_data_size() << "\n";
        std::cout << archiver.get_decompressed_size() << "\n";
        std::cout << archiver.get_metadata_size() << "\n";
    }

    return 0;
}

