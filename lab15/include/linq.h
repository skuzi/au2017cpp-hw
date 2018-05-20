#pragma once

#include <utility>
#include <vector>
#include <iterator>

template<class T, class It>
class range_enumerator;
template<class T>
class drop_enumerator;
template<class T>
class take_enumerator;
template<class T, class U, class F>
class select_enumerator;
template<class T, class F>
class until_enumerator;
template<class T, class F>
class where_enumerator;


template<class T>
class enumerator {
public:
	virtual const T& get_obj() = 0;
	virtual void first() = 0;
	virtual void operator++() = 0; 
	virtual operator bool() = 0;

	auto drop(std::size_t cnt) {
		return drop_enumerator<T>(this, cnt);
	}

	auto take(std::size_t cnt) {
		return take_enumerator<T>(this, cnt);
	}

	template<class U = T, class F>
	auto select(F func) {
		return select_enumerator<U, T, F> (this, func);
	}

	template<class F>
	auto until(F func) {
		return until_enumerator<T, F> (this, func);
	}

	auto until_eq(const T& v) {
		return until([&v](const T& a) { return a == v; });
	}

	template<class F>
	auto where(F func) {
		return where_enumerator<T, F>(this, func);
	}

	auto where_neq(const T& v) {
		return where([&v](const T& a) { return a != v; });
	}


	std::vector<T> to_vector() {
		std::vector<T> res;
		first();
		while (*this) {
			res.push_back(get_obj());
			operator++();
		}
		return res;
	}

	template<class It>
	void copy_to(It it) {
		first();
		while (*this) {
			*it = get_obj();
			it++;
			operator++();
		}
	}
};

template<class T, class It>
class range_enumerator: public enumerator<T> {
public:
	range_enumerator(It& begin, It& end) : begin_(std::move(begin)), end_(std::move(end)) {};
	
	const T& get_obj() {
		return *begin_;
	}
	
	void operator++() { 
		begin_++; 
	}
	
	operator bool() {
		return begin_ != end_;
	}
	
	void first() {}

private:
	It begin_, end_;
};

template<class T>
auto from(T begin, T end) {
	return range_enumerator<typename std::iterator_traits<T>::value_type, T>(begin, end);
}

template<class T>
class drop_enumerator : public enumerator<T> {
public:
	drop_enumerator(enumerator<T> *p, std::size_t cnt) : p_(p), cnt_(cnt) {};

	void first() {
		while (cnt_ > 0) {
		    p_->first();
			cnt_--;
			if (*this)
			    p_->operator++();
		}
	}

	void operator++() {
	    if (*this)
		    p_->operator++();
	}

	const T& get_obj() {
		return p_->get_obj();
	}
	
	operator bool() {
	    return *p_;
	}

private:
	enumerator<T> *p_;
	std::size_t cnt_;
};

template<class T>
class take_enumerator : public enumerator<T> {
public:
	take_enumerator(enumerator<T> *p, std::size_t cnt) : p_(p), cnt_(cnt) {};

	void operator++() {
		if (cnt_ > 0) {
			cnt_--;
			if (*this)
			    p_->operator++();
		}
	}
	
	const T& get_obj() {
		return p_->get_obj();
	}
	
	operator bool() {
	    return (*p_ && cnt_ > 0);
	}
	
	void first() {
		p_->first(); 
	}

private:
	enumerator<T> *p_;
	std::size_t cnt_;
};

template<class T, class U, class F>
class select_enumerator : public enumerator<T> {
public:
	select_enumerator(enumerator<U> *p, F& func) : p_(p), func_(std::move(func)) {};

	const T& get_obj() {
	    obj_ = func_(p_->get_obj());
		return obj_;
	}
	
	void operator++() {
		return p_->operator++();
	}
	
	operator bool() {
	    return *p_;
	}
	
	void first() {
		p_->first();
	}

private:
	enumerator<U> *p_;
	F func_;
	T obj_;
};

template<class T, class F>
class until_enumerator: public enumerator<T> {
public:
	until_enumerator(enumerator<T> *p, F& predicate) : p_(p), predicate_(std::move(predicate)), flag(true) {};

	const T& get_obj() { 
		return p_->get_obj();
	}
	
	void operator++() {
		p_->operator++();
		if (*this && predicate_(get_obj())) {
			flag = false;
		}
	}
	
	operator bool() {
	    return flag && *p_;
	}
	
	void first() { 
	    p_->first();
		if (*this && predicate_(get_obj())) {
			flag = false;
		}
	}

private:
	enumerator<T> *p_;
	F predicate_;
	bool flag;
};

template<class T, class F>
class where_enumerator: public enumerator<T> {
public:
	where_enumerator(enumerator<T> *p, F& predicate) : p_(p), predicate_(std::move(predicate)) {};

	void first() {
	    p_->first();
		while (*this && !predicate_(get_obj())) {
			p_->operator++();
		}
	}

	const T& get_obj() {
		return p_->get_obj();
	}
	
	void operator++() {
		p_->operator++();
		while (*this && !predicate_(get_obj())) {
			p_->operator++();
		}
	}
	
	operator bool() {
	    return *p_;
	}

private:
	enumerator<T> *p_;
	F predicate_;
};