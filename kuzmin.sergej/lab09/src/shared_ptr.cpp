#include "shared_ptr.h"
#include "matrix.h"
shared_ptr::shared_ptr(Matrix* obj) {
	if(obj == NULL)
		storage_ = NULL;
	else
		storage_ = new Storage(obj);
}
shared_ptr::shared_ptr(const shared_ptr& other) {
	storage_ = other.storage_;
	if(!isNull())
		storage_->incr();
}
shared_ptr& shared_ptr::operator=(shared_ptr other) {
	if(&other == this)
		return *this;
	if(!isNull()) {
		storage_->decr();
		if(!storage_->getCounter())
			delete storage_;
	}
	if(!other.isNull()){
		storage_ = other.storage_;
		storage_->incr();
    }
	return *this;
}
shared_ptr::~shared_ptr() {
	if(isNull())
		return;
	storage_->decr();
	if(!storage_->getCounter())
		delete storage_;
}

Matrix* shared_ptr::ptr() const {
	if(isNull())
		return NULL;
	return storage_->getObject();
}
bool shared_ptr::isNull() const {
	return !storage_;
}
void shared_ptr::reset(Matrix* obj) {
	if(isNull()) return;
	storage_->decr();
	if(!storage_->getCounter())
		delete storage_;
	if(obj != NULL)
		storage_ = new Storage(obj);
	else
		storage_ = NULL;
}

Matrix* shared_ptr::operator->() const {
	if(isNull())
		return NULL;
	return storage_->getObject();
}
Matrix& shared_ptr::operator*() const {
	return *storage_->getObject();
}

  
shared_ptr::Storage::Storage(Matrix* mtx) {
	data_ = mtx;
	ref_count_ = 1;
}
shared_ptr::Storage::~Storage() {
	delete data_;
}

void shared_ptr::Storage::incr() {
	ref_count_++;
}
void shared_ptr::Storage::decr() {
	ref_count_--;
}

int shared_ptr::Storage::getCounter() const {
	return ref_count_;
}
Matrix* shared_ptr::Storage::getObject() const {
	return data_;
}