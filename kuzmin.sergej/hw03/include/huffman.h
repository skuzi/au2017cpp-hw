#pragma once
#include <string>
#include <map>
#include <memory>
#include <vector>

typedef std::vector<bool> code_t;
typedef std::map<char, code_t> codetable;
class TreeNode {
friend class HuffmanTree;
public:
    TreeNode(char c = '\0', std::size_t freq = 0, std::shared_ptr<TreeNode> l = nullptr, std::shared_ptr<TreeNode> r = nullptr);
    std::size_t get_freq() const;
    char get_symbol() const;
    std::shared_ptr<TreeNode> get_left() const;
    std::shared_ptr<TreeNode> get_right() const;
    bool is_terminal() const;
    void set_terminal(bool);
private:
    struct compare {
        bool operator()(std::shared_ptr<TreeNode> left, std::shared_ptr<TreeNode> right);
    };
    std::shared_ptr<TreeNode> left, right;
    char symbol = '\0';
    bool terminal = 0;
    std::size_t freq = 0;
};

class HuffmanTree {
public:
    void build_tree();
    void build_codes();
    void encode(std::istream&, std::ostream&);
    void decode(std::istream&, std::ostream&);
private:
    std::map<char, std::size_t> freq;
    std::shared_ptr<TreeNode> root = nullptr;
    std::string data;
    codetable codes;
};