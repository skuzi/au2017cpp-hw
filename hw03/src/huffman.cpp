#include "huffman.h"
#include <iostream>
#include <fstream>
#include <set>
#include <deque>
#include <cassert>
#include <algorithm>

static std::size_t frequency(std::shared_ptr<TreeNode> t) {
    if(t == nullptr)
        return 0;
    return t->get_freq();
}

TreeNode::TreeNode(char c, std::size_t f, std::shared_ptr<TreeNode> l, std::shared_ptr<TreeNode> r): left(l), right(r), symbol(c) {
    freq = frequency(left) + frequency(right) + f;
}


std::size_t TreeNode::get_freq() const {
    return freq;
}

char TreeNode::get_symbol() const {
    return symbol;
}

std::shared_ptr<TreeNode> TreeNode::get_left() const {
    return left;
}

std::shared_ptr<TreeNode> TreeNode::get_right() const {
    return right;
}

bool TreeNode::is_terminal() const {
    return terminal;
}

void TreeNode::set_terminal(bool t) {
    terminal = t;
}

bool TreeNode::compare::operator()(std::shared_ptr<TreeNode> l, std::shared_ptr<TreeNode> r) {
    return frequency(l) < frequency(r);
}

static void make_freq(const std::string& s, std::map<char, std::size_t> &freq) {
    for(char c : s) {
        freq[c]++;
    }
}

static std::string bitvec_to_string(code_t bitvec) {
    std::string result;
    size_t nbits;

    nbits = bitvec.size() & 7;
    result += static_cast<char>(nbits);

    char byte = 0;
    for (unsigned i = 0; i < bitvec.size(); i++) {
        unsigned boff = i & 7;
        byte |= bitvec[i] << boff;
        if (boff == 7) {
            result += byte;
            byte = 0;
        }
    }

    if (nbits) {
        result += byte;
    }

    return result;
}

static code_t string_to_bitvec(std::string s) {
    code_t result;
    unsigned nbits = s[0];

    for (std::string::iterator it = s.begin() + 1; it != s.end(); ++it) {
        for (unsigned i = 0; i < 8; i++) {
            result.push_back((*it >> i) & 1);
        }
    }

    if (nbits) {
        for (unsigned i = 0; i < (8 - nbits); i++) {
            result.pop_back();
        }
    }
    return result;
}

static void go(std::shared_ptr<TreeNode> t, code_t code, codetable &codes) {
    if (t == nullptr)
        return;
    if (t->is_terminal())
        codes[t->get_symbol()] = code;
    
    code_t cpy(code);
    cpy.push_back(1);
    code.push_back(0);

    go(t->get_left(), code, codes);
    go(t->get_right(), cpy, codes);
}

void HuffmanTree::build_codes() {
    go(root, code_t(), codes);
}

void HuffmanTree::decode(std::istream& in, std::ostream& out) {
    std::size_t info_useful = 0;
    std::size_t file_sz = 0;
    std::size_t info_additional = 0;

    in.read(reinterpret_cast<char*> (&info_useful), sizeof(std::size_t));
    
    std::string data;
    for(std::size_t i = 0; i < info_useful; i++){
        char c = '\0';
        if(!in.read(&c, sizeof(char)))
        	throw std::logic_error("File corrupted");
        data.push_back(c);
    }
    
    std::size_t alph_sz = 0;
    info_additional += sizeof(std::size_t);
    
    in.read(reinterpret_cast<char*> (&alph_sz), sizeof(std::size_t));
    for(std::size_t i = 0; i < alph_sz; i++) {
        char symbol = '\0';
        if(!in.read(&symbol, sizeof(char)))
        	throw std::logic_error("File corrupted");
        
        std::size_t frequency = 0;
        if(!in.read(reinterpret_cast<char*> (&frequency), sizeof(std::size_t)))
        	throw std::logic_error("File corrupted");

        freq[symbol] = frequency;
        
        info_additional += sizeof(char) + sizeof(std::size_t);
    }

    build_tree();
    build_codes();
    
    code_t compressed = string_to_bitvec(data);
    
    std::shared_ptr<TreeNode> cur = root;
    for(std::size_t i = 0; i < compressed.size(); i++) {
        if(compressed[i] == 0)
            cur = cur->left;
        else
            cur = cur->right;

        if(cur->is_terminal()) {
            char c = cur->get_symbol();
            out.write(&c, sizeof(char));
            
            file_sz++;
            cur = root;
        }
    }
    std::cout << info_useful << '\n' << file_sz << '\n' << info_additional << '\n';
}

void HuffmanTree::encode(std::istream& in, std::ostream& out) {
    std::string data;
    char c = '\0';
    std::size_t file_sz = 0;
    while(in.read(&c, sizeof(char))) {
        data.push_back(c);
        file_sz += sizeof(char);
    }

    make_freq(data, freq);
    build_tree();
    build_codes();
    
    std::size_t info_useful = 0, info_additional = 0;
    
    code_t result;
    for(char c : data) {
        result.insert(result.end(), codes[c].begin(), codes[c].end());
    }

    std::string res = bitvec_to_string(result);
    
    info_useful = res.size();
    out.write(reinterpret_cast<char*> (&info_useful), sizeof(std::size_t));
    out.write(res.c_str(), info_useful * sizeof(char));


    std::size_t sz = freq.size();
    out.write(reinterpret_cast<char*> (&sz), sizeof(std::size_t));
    info_additional = sizeof(std::size_t);

    for(auto frequency : freq) {
        out.write(&frequency.first, sizeof(char));
        out.write(reinterpret_cast<char*> (&frequency.second), sizeof(std::size_t));
        info_additional += sizeof(char) + sizeof(std::size_t);
    }

    std::cout << file_sz << '\n' << info_useful << '\n' << info_additional << '\n';
}

void HuffmanTree::build_tree() {
    std::multiset<std::shared_ptr<TreeNode>, TreeNode::compare> heap;
    for(auto leaf : freq) {
        auto node = std::make_shared<TreeNode>(TreeNode(leaf.first, leaf.second));
        heap.insert(node);
        node->set_terminal(1);
    }
    root = nullptr;
    
    while (heap.size() > 2) {
        auto left = *heap.begin();
        heap.erase(heap.begin());
        auto right = *heap.begin();
        heap.erase(heap.begin());
        heap.insert(root = std::make_shared<TreeNode>('\0', 0, left, right));
    }
    if(heap.empty())
        return;
    root = std::make_shared<TreeNode>('\0', 0, *heap.begin(), (heap.size() <= 1 ? nullptr : *std::next(heap.begin())));
}
