#include "matrix.h"
#include <utility>
#include <string.h>
#include <iostream>

Matrix::Matrix(std::size_t r, std::size_t c)
	: _rows(r), _cols(c) 
{
	try {
		_data = new int*[_rows];
		if(_data == NULL)
			throw MatrixException("CONSTRUCTOR: memory not allocated.");
	}
	catch(MatrixException& e) {
		std::cout << e.getline();
		exit(0);
	}
	for(std::size_t i = 0; i < _rows; i++) {
		try {
			_data[i] = new int[_cols];
			if(_data[i] == NULL)
				throw MatrixException("CONSTRUCTOR: memory not allocated.");
		}
		catch(MatrixException& e){
			std::cout << e.getline();
		}
		memset(_data[i], 0, _cols * sizeof(int));
	}
}

Matrix::~Matrix() {
	for(std::size_t i = 0; i < _rows; i++) {
		delete [] _data[i];
	}
	delete [] _data;
}

Matrix::Matrix(const Matrix& m) 
	: Matrix(m._rows, m._cols) 
{
	for(std::size_t i = 0; i < _rows; i++) {
		memcpy(_data[i], m._data[i], _cols * sizeof(int));
	}
}

void Matrix::swap(Matrix& m) {
	std::swap(_cols, m._cols);
	std::swap(_rows, m._rows);
	std::swap(_data, m._data);
}

Matrix& Matrix::operator=(const Matrix& m) {
	Matrix(m).swap(*this);
	return *this;
}

std::size_t Matrix::get_rows() const {
    return _rows;
}
std::size_t Matrix::get_cols() const {
	return _cols;
}

void Matrix::set(std::size_t i, std::size_t j, int val) {
	_data[i][j] = val;
}

bool Matrix::check(std::size_t i, std::size_t j) const {
	return i >= 0 && i < _rows && j >= 0 && j < _cols;
}

int Matrix::get(std::size_t i, std::size_t j) const {
	if(!check(i, j))
		throw MatrixException("ACCESS: bad index.");
    return _data[i][j];
}

bool Matrix::operator==(const Matrix& m) const {
    return !(*this != m);
}

bool Matrix::operator!=(const Matrix& m) const {
	if(_rows != m._rows || _cols != m._cols) {
		return true;
	}

    for(std::size_t i = 0; i < _rows; i++) {
    	for(std::size_t j = 0; j < _cols; j++) {
    		if(_data[i][j] != m._data[i][j]) {
    			return true;
    		}
    	}
    }
    return false;
}

Matrix& Matrix::operator+=(const Matrix& m) {
	if(_rows != m._rows || _cols != m._cols)
		throw MatrixException("ADD: dimensions do not match.");
	for(std::size_t i = 0 ; i < _rows; i++) {
		for(std::size_t j = 0 ; j < _cols; j++) {
			_data[i][j] += m._data[i][j];
		}
	}
    return *this;
}

Matrix& Matrix::operator-=(const Matrix& m) {
    return *this += -m;
}

Matrix& Matrix::operator*=(const Matrix& m) {
	if(_cols != m._rows)
		throw MatrixException("MUL: #arg1.columns != #arg2.rows.");

	Matrix a(_rows, m._cols);
	for(std::size_t i = 0; i < _rows; i++) {
		for(std::size_t j = 0; j < m._cols; j++) {
			for(std::size_t k = 0; k < _cols; k++) {
				a._data[i][j] += _data[i][k] * m._data[k][j];
			}
		}
	}
    return *this = a;
}

Matrix Matrix::operator+(const Matrix& m) const {
    return Matrix(*this) += m;
}

Matrix Matrix::operator-(const Matrix& m) const {
    return Matrix(*this) -= m;
}

Matrix Matrix::operator*(const Matrix& m) const {
    return Matrix(*this) *= m;
}

Matrix Matrix::operator-() const {
	Matrix a(*this);
	for(std::size_t i = 0; i < _rows; i++) {
		for(std::size_t j =  0; j < _cols; j++) {
			a._data[i][j] = -_data[i][j];
		}
	}
	return a;
}	