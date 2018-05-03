#include "huffman.h"
#include <iostream>
#include <fstream>
#include <queue>
#include <deque>
#include <cassert>

static std::size_t frequency(shared_ptr<TreeNode> t) {
    if(t == nullptr)
        return 0;
    return t->get_freq();
}

TreeNode::TreeNode(char c, std::size_t f, shared_ptr<TreeNode> l, shared_ptr<TreeNode> r): left(l), right(r), symbol(c) {
    freq = frequency(left) + frequency(right) + f;
}


std::size_t TreeNode::get_freq() const {
    return freq;
}

char TreeNode::get_symbol() const {
    return symbol;
}

shared_ptr<TreeNode> TreeNode::get_left() const {
    return left;
}

shared_ptr<TreeNode> TreeNode::get_right() const {
    return right;
}


bool TreeNode::compare::operator()(shared_ptr<TreeNode> l, shared_ptr<TreeNode> r) {
    return frequency(l) > frequency(r);
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

void HuffmanTree::build_codes() {
    std::deque<std::pair<shared_ptr<TreeNode>, code_t> > q;
    q.push_back(std::make_pair(root, code_t()));
    while (!q.empty()) {
        shared_ptr<TreeNode> node = q.front().first, left_child, right_child;
        code_t code = q.front().second;
        q.pop_front();
        if(node == nullptr)
            continue;
        left_child = node->left;
        right_child = node->right;
        if (left_child) {
            code_t code_cp(code);
            q.push_back({ left_child, (code.push_back(0), code) });
            q.push_back({ right_child, (code_cp.push_back(1), code_cp) });
        } else {
            codes.insert(std::make_pair(node->get_symbol(), code));
        }
    }
}

void HuffmanTree::decode(std::istream& in, std::ostream& out) {
    std::size_t info_useful = 0;
    in.read(reinterpret_cast<char*> (&info_useful), sizeof(std::size_t));
    std::string data;
    for(std::size_t i = 0; i <= info_useful; i++){
        char c = '\0';
        if(!in.read(&c, sizeof(char)))
        	throw std::logic_error("File corrupted");
        data.push_back(c);
    }
    std::size_t alph_sz = 0;
    std::size_t info_additional = sizeof(std::size_t);
    in.read(reinterpret_cast<char*> (&alph_sz), sizeof(std::size_t));
    for(std::size_t i = 0; i < alph_sz * sizeof(char); i++) {
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
    std::size_t file_sz = 0;
    code_t compressed = string_to_bitvec(data);
    shared_ptr<TreeNode> cur = root;
    for(std::size_t i = 0; i < compressed.size(); i++) {
        if(compressed[i] == 0)
            cur = cur->left;
        else
            cur = cur->right;
        if(cur->get_symbol() != '\0') {
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
    info_useful = (result.size() + 7) / 8;
    out.write(reinterpret_cast<char*> (&info_useful), sizeof(std::size_t));
    out.write(res.c_str(), info_useful + 1);


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
    std::priority_queue<shared_ptr<TreeNode>, std::vector<shared_ptr<TreeNode>>, TreeNode::compare> heap;
    for(auto leaf : freq) {
        auto node = std::make_shared<TreeNode>(TreeNode(leaf.first, leaf.second));
        heap.push(node);
    }
    root = nullptr;
    if(heap.size() == 1) {
        auto left = std::make_shared<TreeNode>(TreeNode(heap.top()->get_symbol(), heap.top()->get_freq()));
        root = std::make_shared<TreeNode>(TreeNode(0, 0, left, nullptr));
    }
    else {
        while(heap.size() > 1) {
            shared_ptr<TreeNode> l(heap.top());
            heap.pop();
            shared_ptr<TreeNode> r(heap.top());
            heap.pop();
            root = std::make_shared<TreeNode>(TreeNode(0, 0, l, r));
            heap.push(root);
        }
    }
}
