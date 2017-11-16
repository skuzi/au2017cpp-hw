#include "my_vector.h"

MyVector::MyVector()
    : _sz(0), _cp(2) {
    _data = new int[_cp]; 
}

MyVector::MyVector(std::size_t init_capacity)
    : _sz(0), _cp(init_capacity) {
    _data = new int[_cp];
}
MyVector::~MyVector() {
    delete [] _data;
}

void MyVector::set(std::size_t index, int value) {
    _data[index] = value;
}

int MyVector::get(std::size_t index) {
    return _data[index];
}

std::size_t MyVector::size() {
    return _sz;
}

std::size_t MyVector::capacity() {
    return _cp;
}

void MyVector::reserve(std::size_t new_capacity) {
    if(new_capacity <= _cp)
        return;

    _cp = new_capacity;
    int *tmp = new int[_cp];
    for(std::size_t i = 0; i < _sz; i++)
        tmp[i] = _data[i];

    delete [] _data;
    _data = tmp;
}

void MyVector::resize(std::size_t new_size) {
    std::size_t new_cp = _cp;
    if (new_size > _cp)
        new_cp = (new_size > 2 * _cp ? new_size : 2 * _cp);

    reserve(new_cp);
    for (std::size_t i = _sz; i < new_size; i++) {
        _data[i] = 0;
    }

    _sz = new_size;
    _cp = new_cp;
}

void MyVector::push_back(int value) {
    if(_sz + 1 > _cp)
        reserve(2 * _cp);

    _data[_sz++] = value;
}

void MyVector::insert(std::size_t index, int value) {
    if(_sz + 1 > _cp)
        reserve(2 * _cp);

    for(std::size_t i = _sz++; i > index; i--) {
        _data[i] = _data[i - 1];
    }

    _data[index] = value;
}

void MyVector::erase(std::size_t index) {
    _sz--;

    for(std::size_t i = index; i < _sz; i++) {
        _data[i] = _data[i + 1];
    }
}