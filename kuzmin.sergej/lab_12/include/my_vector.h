#pragma once
#include <cstddef>
#include <iostream>

template <class T>
class my_vector{
public:
    my_vector();
    my_vector(size_t n);
    my_vector(my_vector& other);
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

    void push_back(T& t);
    void pop_back();
    void clear();

private:
    size_t size_;
    size_t capacity_;
    T* array_;
};

template<class T>
my_vector<T>::my_vector():
	size_(0), capacity_(1)
{		
	array_ = new T[2];
}

template<class T>
my_vector<T>::my_vector(size_t n):
	size_(0), capacity_(n)
{
	array_ = new T[n];
}

template<class T>
my_vector<T>::my_vector(my_vector<T>& other):
	size_(other.size_), capacity_(other.capacity_)
{
	array_ = new T[capacity_];
	for(size_t i = 0; i < size_; i++)
		array_[i] = other[i];
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

	while(capacity_ < n)
		capacity_ *= 2;

	T* tmp = new T[capacity_];
	for(size_t i = 0; i < size_; i++)
		tmp[i] = array_[i];
	
	delete [] array_;
	array_ = tmp;
}

template<class T>
void my_vector<T>::resize(size_t n) {
	reserve(n);
	if(n < size_)
		for(size_t i = n; i < size_; i++)
			array_[i].~T();
	size_ = n;
}

template<class T>
T my_vector<T>::operator[](size_t index) const {
	return array_[index];
}

template<class T>
T& my_vector<T>::operator[](size_t index) {
	return array_[index];
}

template<class T>
void my_vector<T>::push_back(T& t) {
	reserve(size_ + 1);
	array_[size_++] = t;
}

template<class T>
void my_vector<T>::pop_back() {
	size_--;
}

template<class T>
void my_vector<T>::clear() {
	while(!empty())
		pop_back();
}
