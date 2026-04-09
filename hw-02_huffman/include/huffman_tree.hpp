#ifndef HUFFMAN_TREE
#define HUFFMAN_TREE

#include <unordered_map>
#include <cstdint>

class HuffmanTreeNode {
private:
    std::uint64_t frequency;
    std::uint8_t symbol;
    HuffmanTreeNode* left_child;
    HuffmanTreeNode* right_child;
public:
    HuffmanTreeNode* get_left_child() const;
    HuffmanTreeNode* get_right_child() const;
    std::uint8_t get_symbol() const;
    std::uint64_t get_frequency() const;

    HuffmanTreeNode();
    HuffmanTreeNode(std::uint8_t my_symbol, std::uint64_t my_frequency);
    HuffmanTreeNode(HuffmanTreeNode* my_left, HuffmanTreeNode* my_right);
    bool is_leaf() const;
};

class HuffmanTree {
private:
    HuffmanTreeNode* root;

    HuffmanTreeNode* deserialize_node(std::istream& in);
    void delete_subtree(HuffmanTreeNode* node);

public:
    HuffmanTree();
    HuffmanTree(HuffmanTreeNode* my_root);
    ~HuffmanTree();
    HuffmanTreeNode* get_root();

    void serialize_tree(std::ostream& out, HuffmanTreeNode* root);
    HuffmanTreeNode* deserialize_tree(std::istream& in);
    HuffmanTreeNode* build_from_frequencies(const std::unordered_map<std::uint8_t, std::uint64_t>& freqs);
    void decode(std::istream& in, std::ostream& out);

};

struct Compare {
    bool operator()(HuffmanTreeNode* left, HuffmanTreeNode* right) {
        return left->get_frequency() > right->get_frequency();
    }
};

void build_codes_recursive(HuffmanTreeNode* node, const std::string& current_code , std::unordered_map<std::uint8_t, std::string>& codes);

#endif //HUFFMAN_TREE