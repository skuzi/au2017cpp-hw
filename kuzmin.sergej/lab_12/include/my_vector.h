#pragma once
#include <cstddef>
#include <iostream>
#include <new>

template <class T>
class my_vector{
public:
    my_vector();
    my_vector(size_t n);
    my_vector(const my_vector& other);
    my_vector& operator=(my_vector other);
    ~my_vector();

    size_t size() const { return size_; }
    size_t capacity() const { return capacity_; }
    bool empty() const { return size_ == 0; }

    void resize(size_t n);
    void reserve(size_t n);

    T operator[](size_t index) const;
    T& operator[](size_t index);

    friend std::ostream& operator<<(std::ostream& os, const my_vector& a) {
    	for(size_t i = 0; i < a.size(); i++)
    		os << a[i] << ' ';
    	return os;
    }

    void push_back(const T& t);
    void pop_back();
    void clear();

private:
    size_t size_;
    size_t capacity_;
    int8_t* array_;
};

static int pow2(int n) {
	int t = 1;
	while(t < n)
		t *= 2;
	return t;		
}

template<class T>
my_vector<T>::my_vector():
	size_(0), capacity_(1), array_(new int8_t[sizeof(T)]) {}

template<class T>
static void new_el(int8_t* array, size_t index, const T& el) {
	new (array + index * sizeof(T)) T(el);
}

template<class T>
my_vector<T>::my_vector(size_t n):
	size_(n), capacity_(pow2(n)), array_(new int8_t[size_ * sizeof(T)])
{
	for(size_t i = 0; i < size_; i++)
		new_el(array_, i, T());
}


template<class T>
my_vector<T>::my_vector(const my_vector<T>& other):
	size_(other.size_), capacity_(other.capacity_), array_(new int8_t[capacity_ * sizeof(T)])
{
	for(size_t i = 0; i < size_; i++)
		new_el(array_, i, other[i]);
}

template<class T>
my_vector<T>& my_vector<T>::operator=(my_vector<T> other) {
	std::swap(array_, other.array_);
	std::swap(size_, other.size_);
	std::swap(capacity_, other.capacity_);
	return *this;
}

template<class T>
my_vector<T>::~my_vector() {
	clear();
	delete [] array_;
}

template<class T>
void my_vector<T>::reserve(size_t n) {
	if(n <= capacity_)
		return;

	capacity_ = pow2(n);
	int8_t* tmp = new int8_t[capacity_ * sizeof(T)];
	for(size_t i = 0; i < size_; i++)
		new_el(tmp, i, (*this)[i]);
	
	for(size_t i = 0; i < size_; i++)
		(*this)[i].~T();
	delete [] array_;
	array_ = tmp;
}

template<class T>
void my_vector<T>::resize(size_t n) {
	reserve(n);
	if(n < size_)
		for(size_t i = n; i < size_; i++)
			(*this)[i].~T();
	else
		for(size_t i = size_; i < n; i++)
			new_el(array_, i, T());
	size_ = n;
}

template<class T>
T my_vector<T>::operator[](size_t index) const {
	return *((T*)(array_ + index * sizeof(T)));
}

template<class T>
T& my_vector<T>::operator[](size_t index) {
	return *((T*)(array_ + index * sizeof(T)));
}

template<class T>
void my_vector<T>::push_back(const T& t) {
	reserve(size_ + 1);
	new_el(array_, size_++, t);
}

template<class T>
void my_vector<T>::pop_back() {
	size_--;
	(*this)[size_].~T();
}

template<class T>
void my_vector<T>::clear() {
	while(!empty())
		pop_back();
}
