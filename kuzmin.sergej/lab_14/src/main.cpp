#include <string>
#include <vector>
#include <iostream>
#include <cstdio>
#include <cassert>
#include <fstream>

#include "matrix.h"

using std::cin;
using std::cout;

int main(int, char **) {
  std::string cmd, arg1, arg2;
  std::vector<Matrix> vars;
  vars.reserve(10);
  for(std::size_t i = 0; i <= 9; i++) {
    vars.push_back(Matrix(0, 0));
  }
  while (cin) {
    cin >> cmd;
    try{
      if (cmd == "exit") {
        break;
      } else if (cmd == "load") {
        cin >> arg1 >> arg2;

        std::ifstream in(arg2, std::ifstream::in);
        std::size_t rows, cols;
        
        in >> rows >> cols;
        
        Matrix m(rows, cols);
        for(std::size_t i = 0; i < rows; i++) {
          for(std::size_t j = 0; j < cols; j++) {
            int32_t val;
            in >> val;
            m.set(i, j, val);
          }
        }
        vars[arg1[1] - '0'] = m;
      } else if (cmd == "print") {
        cin >> arg1;
        cout << vars[arg1[1] - '0'];
      } else if (cmd == "add") {
        cin >> arg1 >> arg2;
        vars[arg1[1] - '0'] += vars[arg2[1] - '0'];
      } else if (cmd == "mul") {
        cin >> arg1 >> arg2;
        vars[arg1[1] - '0'] *= vars[arg2[1] - '0'];
      } else if (cmd == "elem") {
        cin >> arg1;
        int i, j;
        cin >> i >> j;
        cout << vars[arg1[1] - '0'].get(i, j) << '\n';
      } 
    }
    catch(MatrixException &e) {
      cout << e.getline();
    }
  }

}