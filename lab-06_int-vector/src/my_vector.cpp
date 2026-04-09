#include "my_vector.hpp"
#include <algorithm>

std::size_t BasicValue = 2;

MyVector::MyVector() {
    _size = 0;
    _capacity = BasicValue;
    _data = new int[_capacity];
}

MyVector::MyVector(std::size_t init_capacity) {
    _size = 0;
    _capacity = init_capacity;
    _data = new int[_capacity];
}

MyVector::~MyVector(){
    delete[] _data;
}

MyVector::MyVector(const MyVector& other) {
    *this = other;
}

MyVector& MyVector::operator=(const MyVector& other) {
    if (this == &other) {
        return *this;
    }
    delete[] _data;
    _size = other._size;
    _capacity = other._capacity;
    _data = new int[_capacity];

    std::copy(other._data, other._data + _size, _data);
    return *this;
}

void MyVector::set(std::size_t index, int value) {
    if (index < _size) {
        _data[index] = value;
    }
}

int MyVector::get(std::size_t index) {
    int elem = _data[index];
    return elem;
}

std::size_t MyVector::size() {
    return _size;
}

std::size_t MyVector::capacity() {
    return _capacity;
}

void MyVector::reserve(std::size_t new_capacity) {
    if (new_capacity <= _capacity) {
        return;
    }

    int* new_data = new int[new_capacity];
    for (std::size_t i = 0; i < _size; i++) {
        new_data[i] = _data[i];
    }

    delete[] _data;
    _data = new_data;
    _capacity = new_capacity;
}


void MyVector::resize(std::size_t new_size) { 
    if ( new_size > _capacity) {
        std::size_t new_capacity = std::max(new_size, 2 * _capacity);
        reserve(new_capacity);
    }

    if (new_size > _size) {
        for (std::size_t i = _size; i < new_size; ++i) {
            _data[i] = 0;
        }
    }
    _size = new_size;
}

void MyVector::push_back(int value) {
    if ( _size == _capacity){
        std::size_t new_capacity = _capacity * 2;
        int * new_data = new int[new_capacity];
        
        for (std:: size_t i = 0; i < _size; i++) {
            new_data[i] = _data[i];
        }
        delete[] _data;
        _data = new_data;
        _capacity = new_capacity;
    }

    _data[_size] = value;
    ++_size;
}

void MyVector::insert(std::size_t index, int value) {
    if (_size == _capacity) {
        reserve(_capacity * 2);
    }

    if (index == _size) {
        _data[index] = value;
        ++_size;

    } else {
        for (std::size_t i = _size; i > index; --i) {
            _data[i] = _data[i - 1];
        }
        _data[index] = value;
        ++_size;
    }
}

void MyVector::erase(std::size_t index) {
    for (std::size_t i = index; i < _size - 1; ++i) {
        _data[i] = _data[i + 1];
    }
    -- _size;
}
