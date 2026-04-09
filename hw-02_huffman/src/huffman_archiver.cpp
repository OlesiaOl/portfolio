
#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
#include <string>
#include <cstdint>
#include "huffman_archiver.hpp"
#include "huffman_tree.hpp"

void HuffmanArchiver::encode(std::istream& in, std::ostream& out) {
    std::unordered_map<std::uint8_t, std::uint64_t> freq_table;
    std::vector<std::uint8_t> data;
    char cur;

    while (in.get(cur)) {
        std::uint8_t byte = static_cast<std::uint8_t>(cur);
        freq_table[byte]++;
        data.push_back(byte);
    }

    original_size_ = data.size();

    HuffmanTree tree;
    HuffmanTreeNode* root = tree.build_from_frequencies(freq_table);
    if (!root) return;

    tree.serialize_tree(out, root);
    out.write(reinterpret_cast<const char*>(&original_size_), sizeof(std::size_t));

    std::size_t start_pos = out.tellp();

    std::unordered_map<std::uint8_t, std::string> codes;
    build_codes_recursive(root, "", codes);

    std::string bit_string;
    for (std::uint8_t byte : data) {
        bit_string += codes.at(byte);
    }

    std::uint8_t buffer = 0;
    int bit_count = 0;

    for (std::size_t i = 0; i < bit_string.size(); ++i) {
        char bit = bit_string[i];
        buffer <<= 1;
        if (bit == '1') {
            buffer |= 1;
        }
        bit_count++;
        if (bit_count == 8) {
            out.put(static_cast<char>(buffer));
            buffer = 0;
            bit_count = 0;
        }
    }
    if (bit_count > 0) {
        buffer <<= (8 - bit_count);
        out.put(static_cast<char>(buffer));
    }

    std::size_t end_pos = out.tellp();
    compressed_data_size_ = end_pos - start_pos;
    metadata_size_ = start_pos;
}

void HuffmanArchiver::decode(std::istream& in, std::ostream& out) {

    std::streampos start_pos_stream = in.tellg();
    std::streampos start_pos = start_pos_stream;

    HuffmanTree tree;
    tree.deserialize_tree(in);

    if (tree.get_root() == nullptr) {
        compressed_data_size_ = 0;
        decompressed_size_ = 0;
        original_size_ = 0;
        metadata_size_ = 0;
        return;
    }

    std::size_t expected_size = 0;

    if (!in.read(reinterpret_cast<char*>(&expected_size), sizeof(std::size_t))) {
        compressed_data_size_ = 0;
        decompressed_size_ = 0;
        original_size_ = 0;
        metadata_size_ = static_cast<std::size_t>(in.tellg()) - start_pos;
        return;
    }

    if (tree.get_root()->is_leaf()) {
        std::uint8_t symbol = tree.get_root()->get_symbol();

        std::streampos data_start = in.tellg();
        in.seekg(0, std::ios::end);
        in.seekg(data_start);

        compressed_data_size_ = 1;

        for (std::size_t i = 0; i < expected_size; ++i) {
            out.put(static_cast<char>(symbol));
        }

        decompressed_size_ = expected_size;
        original_size_ = expected_size;

        std::streampos after_tree_stream = in.tellg();
        metadata_size_ = static_cast<std::size_t>(after_tree_stream - start_pos) - 1;

        return;
    }

    std::streampos after_tree_stream = in.tellg();
    std::size_t after_tree = static_cast<std::size_t>(after_tree_stream);
    metadata_size_ = after_tree - start_pos;

    if (expected_size == 0) {
        compressed_data_size_ = 0;
        decompressed_size_ = 0;
        original_size_ = 0;
        return;
    }

    HuffmanTreeNode* current = tree.get_root();
    char byte;
    std::size_t decompressed_size = 0;
    std::size_t compressed_bytes = 0;

    bool got_any_bits = false;
    if (current->is_leaf()) {
        char symbol = static_cast<char>(current->get_symbol());
        for (std::size_t i = 0; i < expected_size; ++i) {
            out.put(symbol);
        }

        compressed_data_size_ = 1;
        decompressed_size_ = expected_size;
        original_size_ = expected_size;
        return;
    }

    while (in.get(byte)) {
        got_any_bits = true;
        compressed_bytes++;

        for (int i = 7; i >= 0; --i) {
            int bit = (byte >> i) & 1;
            current = (bit == 0) ? current->get_left_child() : current->get_right_child();

            if (!current) {
                compressed_data_size_ = compressed_bytes;
                decompressed_size_ = decompressed_size;
                original_size_ = expected_size;
                return;
            }

            if (current->is_leaf()) {
                char symbol = static_cast<char>(current->get_symbol());
                out.put(symbol);
                decompressed_size++;
                current = tree.get_root();

                if (decompressed_size == expected_size) {
                    compressed_data_size_ = compressed_bytes;
                    decompressed_size_ = decompressed_size;
                    original_size_ = expected_size;
                    return;
                }
            }
        }
    }
    if (!got_any_bits) {
        compressed_data_size_ = 0;
        decompressed_size_ = 0;
        original_size_ = expected_size;
        return;
    }

    compressed_data_size_ = compressed_bytes;
    decompressed_size_ = decompressed_size;
    original_size_ = expected_size;
}
