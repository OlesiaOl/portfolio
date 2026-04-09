#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
#include <cstdint>

#include "huffman_tree.hpp"

HuffmanTreeNode* HuffmanTreeNode::get_left_child() const {
    return left_child;
}
HuffmanTreeNode* HuffmanTreeNode::get_right_child() const {
    return right_child;
}
std::uint8_t HuffmanTreeNode::get_symbol() const {
    return symbol;
}
std::uint64_t HuffmanTreeNode::get_frequency() const {
    return frequency;
}

HuffmanTreeNode::HuffmanTreeNode()
    : frequency(0),symbol(0),left_child(nullptr), right_child(nullptr) {}

bool HuffmanTreeNode::is_leaf() const {
    return right_child == nullptr && left_child == nullptr;
}

HuffmanTreeNode::HuffmanTreeNode(std::uint8_t my_symbol, std::uint64_t my_frequency) 
    : frequency(my_frequency), symbol(my_symbol), left_child(nullptr), right_child(nullptr) {}

HuffmanTreeNode::HuffmanTreeNode(HuffmanTreeNode* my_left, HuffmanTreeNode* my_right) 
    : frequency(my_left->get_frequency() + my_right->get_frequency()),
     symbol(0), left_child(my_left), right_child(my_right) {}

HuffmanTree::HuffmanTree()
    : root(nullptr) {}

HuffmanTree::HuffmanTree(HuffmanTreeNode* my_root) 
    : root(my_root) {}

HuffmanTree::~HuffmanTree() {
    delete_subtree(root);
}

HuffmanTreeNode* HuffmanTree::get_root() {
    return root;
}


void HuffmanTree::delete_subtree(HuffmanTreeNode* node) {
    if (!node) {
        return;
    }
    delete_subtree(node->get_left_child());
    delete_subtree(node->get_right_child());
    delete node;
}


HuffmanTreeNode* HuffmanTree::build_from_frequencies(const std::unordered_map<std::uint8_t, std::uint64_t>& freqs) {
    std::priority_queue<HuffmanTreeNode*, std::vector<HuffmanTreeNode*>, Compare> my_queue;
    for (std::unordered_map<std::uint8_t, std::uint64_t>::const_iterator it = freqs.begin(); it != freqs.end(); ++it) {
        std::uint8_t symbol = it->first;
        std::uint64_t frequency = it->second;
        HuffmanTreeNode* node = new HuffmanTreeNode(symbol, frequency);
        my_queue.push(node);
    }
    if (my_queue.empty()) {
        root = nullptr;
        return nullptr;
    }
    while (my_queue.size() > 1) {
        HuffmanTreeNode* left = my_queue.top();
        my_queue.pop();
        HuffmanTreeNode* right = my_queue.top();
        my_queue.pop();
        HuffmanTreeNode* transition_element = new HuffmanTreeNode(left, right);
        my_queue.push(transition_element);
    }
    root = my_queue.top();
    return root;
}

void build_codes_recursive(HuffmanTreeNode* node, const std::string& current_code , std::unordered_map<std::uint8_t, std::string>& codes) {
    if (!node) {
        return;
    }
    
    if (node->is_leaf()) {
        codes[node->get_symbol()] = current_code;
        return;
    }

    build_codes_recursive(node->get_left_child(), current_code + "0", codes);
    build_codes_recursive(node->get_right_child(), current_code + "1", codes);
}

void HuffmanTree::serialize_tree(std::ostream& out, HuffmanTreeNode* root) {
    if (!root) {
        return;
    }
    if (root->is_leaf()) {
        out.put(1);
        out.put(root->get_symbol());
    } else {
        out.put(0);
        serialize_tree(out, root->get_left_child());
        serialize_tree(out, root->get_right_child());
    }
}

HuffmanTreeNode* HuffmanTree::deserialize_tree(std::istream& in) {
    root = deserialize_node(in);
    return root;
}

HuffmanTreeNode* HuffmanTree::deserialize_node(std::istream& in) {
    int flag = in.get();
    if (flag == EOF) return nullptr;

    if (flag == 1) {
        int sym = in.get();
        if (sym == EOF) return nullptr;
        return new HuffmanTreeNode(static_cast<std::uint8_t>(sym), 0);
    } else if (flag == 0) {
        HuffmanTreeNode* left = deserialize_node(in);
        if (!left) return nullptr;

        HuffmanTreeNode* right = deserialize_node(in);
        if (!right) {
            delete left;
            return nullptr;
        }

        return new HuffmanTreeNode(left, right);
    } else {
        return nullptr;
    }
}
