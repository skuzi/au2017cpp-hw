#include "huffman.h"
#include <string>
#include <cstring>
#include <exception>
#include <fstream>
#include <iostream>

class bad_pars_exception : public std::exception {
public:
    const char* what() const throw() {
        return "Bad parameters!\nUsage: -c/-u -f/--file input_name -o/--output output_name\n";
    }
};

void get_pars(int argc, char **argv, std::string& in_file, std::string& out_file, char& type) {
    if(argc != 6)
        throw bad_pars_exception();
    for(int i = 1; i < argc; i++) {
        if(!strcmp(argv[i], "-c")){
            type = 'c';
        }
        else if(!strcmp(argv[i], "-u")) {
            type = 'u';
        }
        else if(!strcmp(argv[i], "-f") || !strcmp(argv[i], "--file")) {
            if(i == argc - 1)
                throw bad_pars_exception();
            in_file = argv[i + 1];
            i++;
        }
        else if(!strcmp(argv[i], "-o") || !strcmp(argv[i], "--output")) {
            if(i == argc - 1)
                throw bad_pars_exception();
            out_file = argv[i + 1];
            i++;
        }
        else
            throw bad_pars_exception();
    }
}

int main(int argc, char **argv) {
    std::string in_file, out_file;
    char type;
    try {
        get_pars(argc, argv, in_file, out_file, type);
    }
    catch(const std::exception& exc) {
        std::cout << exc.what();
        return 1;
    }
    std::ifstream in(in_file, std::ios::in | std::ios::binary);
    std::ofstream out(out_file, std::ios::out | std::ios::binary);
    try{
        HuffmanTree tree;
        if(type == 'u') {
            tree.decode(in, out);
        }
        else {
            tree.encode(in, out);
        }
    }catch(const std::exception& exc) {
        std::cout << exc.what();
        return 1;
    }
    return 0;
}