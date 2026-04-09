#include "shared_ptr.hpp"

shared_ptr::~shared_ptr() {
    if ( storage_ ) {
        storage_->decr();
        if (storage_->getCounter() == 0 ){
            delete storage_;
        }
    }
}

shared_ptr::shared_ptr(Matrix* obj) {
    if (obj != nullptr) {
        storage_ = new Storage(obj);
    } else {
        storage_ = nullptr;
    }
}

shared_ptr::shared_ptr(const shared_ptr& other) {
    if (other.storage_) {
        storage_ = other.storage_;
        storage_->incr();
    } else {
        storage_ = nullptr;
    }
}

shared_ptr& shared_ptr::operator=(shared_ptr other) {
    if (this == &other) {
        return *this;
    }
    if (storage_ != nullptr) {
        storage_->decr();
        if (storage_->getCounter() == 0) {
            delete storage_;
        }
    }
    storage_ = other.storage_;
    if (storage_) {
        storage_->incr();
    }

    return *this;
}

Matrix* shared_ptr::ptr() const {
    if (storage_ == nullptr) {
        return nullptr;
    } 
    return storage_->getObject();
}

bool shared_ptr:: isNull() const {
    if (storage_ == nullptr) {
        return true;
    } else {
        return false;
    }
}

void shared_ptr::reset(Matrix* obj) {
    if (storage_ != nullptr) {
        storage_->decr();
        if (storage_->getCounter() == 0) {
            delete storage_;
        }
    }

    if (obj != nullptr) {
        storage_ = new Storage(obj);
    } else {
        storage_ = nullptr;
    }
}

Matrix* shared_ptr::operator->() const {
    if (storage_ == nullptr) {
        return nullptr;
    } else {
        return storage_->getObject();
    }
}

Matrix& shared_ptr::operator*() const {
        return *(storage_->getObject());
}


shared_ptr::Storage::Storage(Matrix* mtx) : data_(mtx), ref_count_(1){}

shared_ptr::Storage::~Storage() {
    delete data_;
}

void shared_ptr::Storage::incr() {
    ++ref_count_;
}
void shared_ptr::Storage::decr() {
    --ref_count_;
}

int shared_ptr::Storage::getCounter() const {
    return ref_count_;
}
Matrix* shared_ptr::Storage::getObject() const {
    return data_;
}