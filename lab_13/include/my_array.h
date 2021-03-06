#include <cassert>
#include <cstring>

template<typename T, std::size_t N>
class my_array {
public:
  T& at(std::size_t index) {
  	assert(index >= 0 && index < N);
  	return arr_[index];
  }

  const T& at(std::size_t index) const {
  	assert(index >= 0 && index < N);
  	return arr_[index];
  }

  const T& operator[](std::size_t index) const {
  	return arr_[index];
  }

  T& operator[](std::size_t index) {
  	return arr_[index];
  }

  bool empty() const {
  	return size() == 0;
  }
  std::size_t size() const {
  	return N;
  }

  void fill(T val) {
  	for(std::size_t i = 0; i < N; i++)
  		arr_[i] = val;
  }
private:
	T arr_[N];
};

class ProxyBool {
public:
	ProxyBool(char* b, int pos) : pr_(b), pos_(pos) {}
	~ProxyBool() {}

	ProxyBool& operator=(bool other) {
		*pr_ ^= (-other ^ *pr_) & (1UL << pos_);
		return *this;
	}

	operator bool() const{
		return (*pr_ >> pos_) & 1;
	}

	ProxyBool& operator=(const ProxyBool& other) {
		return *this = bool(other);
	}

private:
	char *pr_;
	int pos_;
};


template<std::size_t N>
class my_array<bool, N> {
public:
	my_array() {
		fill(0);
	}
	bool empty() const {
		return size() == 0;
	}

	bool operator[](std::size_t index) const {
		return (arr_[index / 8] >> (index % 8)) & 1;
	}

	ProxyBool operator[](std::size_t index) {
		return ProxyBool(arr_ + index / 8, index % 8);
	}

	bool at(std::size_t index) const {
		assert(index >= 0 && index < N);
		return (*this)[index];
	}

	ProxyBool at(std::size_t index) {	
		assert(index >= 0 && index < N);
		return (*this)[index];
	}

	std::size_t size() const {
		return N;
	}

	void fill(bool bit) {
		memset(arr_, -bit, sizeof(arr_));
	}
private:
	char arr_[(N + 7) / 8];
};
