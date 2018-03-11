#include <iostream>
#include <cstring>
#include <cassert>

#include "my_vector.h"

class Product {
public:
    Product(const char* name, int quantity, double price):
    	name_(new char[strlen(name) + 1]), quantity_(quantity), price_(price)
    {
    	strcpy(name_, name);
    }

    Product():
    	name_(new char[8]), quantity_(0), price_(0)
    {
    	strncpy(name_, "DEFNAME", 8);
    }

    Product(const Product& other):
    	name_(new char[strlen(other.name_) + 1]), quantity_(other.quantity_), price_(other.price_)
    {
    	strcpy(name_, other.name_);
    }

    int quantity() const { return quantity_; }
    double price() const { return price_; }
    char* name() const {return name_; }

    Product& operator=(Product p) {
        delete [] name_;
        name_ = new char[strlen(p.name_) + 1];
        strcpy(name_, p.name_);
    	std::swap(quantity_, p.quantity_);
    	std::swap(price_, p.price_);
    	return *this;
    }

    friend std::ostream& operator<<(std::ostream& os, const Product& s) {
    	os << s.name() << ' ' << s.quantity() << ' ' << s.price();
    	return os;
    }

    ~Product() {
   		delete [] name_;
    }

private:
    char *name_;
    int quantity_;
    double price_;
};

void print(const my_vector<Product>& v) {
    std::cout << v << std::endl;
}

template<class T>
void test_my_vector(my_vector<T>& a) {
    size_t t = a.size();
    a.push_back(T());
    std::cout << a;
	assert(a.size() == t + 1);
	a.pop_back();
	assert(a.size() == t);
	a.clear();
	assert(a.size() == 0);
	assert(a.empty());
	a.push_back(T());
	assert(a.size() == 1);
	a.reserve(3);

	assert(a.size() == 1);
	assert(a.capacity() == 4);
	a.reserve(2);
	assert(a.capacity() == 4);
	assert(a.size() == 1);
	a.resize(3);
	assert(a.size() == 3);
	assert(a.capacity() == 4);
	a.push_back(T());
	assert(a.size() == 4);
	assert(a.capacity() == 4);
	a.push_back(T());
	assert(a.size() == 5);
	assert(a.capacity() == 8);
    a.resize(50);
    assert(a.capacity() == 64);
    std::cout << a << std::endl;
    a.resize(2);
    assert(a.size() == 2);
    assert(a.capacity() == 64);
    std::cout << a << std::endl;
    a.resize(0);
    assert(a.empty());
    assert(a.capacity() == 64);
    std::cout << a << std::endl;
    a.reserve(100);
    assert(a.size() == 0);
    assert(a.capacity() == 128);
    a.reserve(80);
    assert(a.capacity() == 128);
    a.resize(50);
    assert(a.size() == 50);
    assert(a.capacity() == 128);
    std::cout << a << std::endl;
    my_vector<T> b(10);
    std::cout << b << std::endl;
    a = b;
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    a.push_back(T());
    assert(b.size() == 10);
    assert(a.size() == 11);
    assert(b.capacity() == 16);
    assert(a.capacity() == 16);
}

int main() {
	my_vector<int> a;
	int c = 5;
	a.push_back(c += 5);
	a.push_back(c);
    test_my_vector<int>(a);
    my_vector<Product> b;
    Product d, e("qwe", -1, 7.5);
    b.push_back(Product("qwe", -1, 7.5));
    b.push_back(d);
    test_my_vector<Product>(b);
    
    return 0;
}

