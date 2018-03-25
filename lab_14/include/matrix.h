#ifndef LAB_08_MATRIX_H
#define LAB_08_MATRIX_H

#include <cstdio>
#include <string>
#include <cstring>
#include <iostream>
#include <cstddef>

class Matrix {
public:
  Matrix(std::size_t r, std::size_t c);
  Matrix(const Matrix &);
  ~Matrix();
  Matrix& operator=(const Matrix&);

  std::size_t get_rows() const;
  std::size_t get_cols() const;
  void set(std::size_t i, std::size_t j, int val);
  int get(std::size_t i, std::size_t j) const;
  
  friend std::ostream& operator<<(std::ostream& os, const Matrix& a) {
    for(std::size_t i = 0; i < a._rows; i++) {
      for(std::size_t j = 0; j < a._cols; j++) {
        os << a._data[i][j] << ' ';
      }
      os << '\n';
    }
    return os;
}

  Matrix operator+(const Matrix& m) const;
  Matrix operator-(const Matrix& m) const;
  Matrix operator*(const Matrix& m) const;

  Matrix& operator+=(const Matrix& m);
  Matrix& operator-=(const Matrix& m);
  Matrix& operator*=(const Matrix& m);

  bool operator==(const Matrix& m) const;
  bool operator!=(const Matrix& m) const;

  Matrix operator-() const;
private:
  bool check(std::size_t i, std::size_t j) const;
  std::size_t _rows;
  std::size_t _cols;
  void swap(Matrix &m);
  int32_t **_data;
};

class MatrixException {
public:
  MatrixException(const std::string& s): text(s + "\n") {}
  const std::string& getline() const {
    return text;
  }
  ~MatrixException() {}
private:
  std::string text;
};

#endif