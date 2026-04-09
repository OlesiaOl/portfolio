#include "my_vector.hpp"

#include <stdexcept>
#include <utility>
#include <iostream>
#include <stdexcept>
#include <cassert>

namespace containers {

template<typename T>
my_vector<T>::my_vector() : capacity_(INITIAL_CAPACITY), size_(0) {
    array_ = static_cast<T*>(::operator new[](sizeof(T) * capacity_));
}

template<typename T>
std::size_t my_vector<T>::calculate_capacity(std::size_t n) const {
    std::size_t capacity = 1;
    while (capacity < n) {
        capacity <<= 1;
    }
    return capacity;
}

template<typename T>
my_vector<T>::my_vector(std::size_t n) : size_(n) {
    capacity_ = calculate_capacity(n);
    array_ = static_cast<T*>(::operator new[](capacity_ * sizeof(T)));

    if (std::is_default_constructible_v<T>) {
        for (std::size_t i = 0; i < n; ++i) {
            new (array_ + i) T();
        }
    }
}

template<typename T>
my_vector<T>::my_vector(const my_vector& other)
    : capacity_(other.capacity_), size_(other.size_), array_(static_cast<T*>(::operator new[](other.capacity_ * sizeof(T)))) {
    for (std::size_t i = 0; i < other.size_; ++i) {
        new (array_ + i) T(other.array_[i]);
    }
}

template<typename T>
my_vector<T>& my_vector<T>::operator=(const my_vector other) {
    if (&other == this) {
        return *this;
    }

    clear();
    ::operator delete[](array_);
    capacity_ = other.capacity_;
    size_ = other.size_;
    array_ = static_cast<T*>(::operator new[](capacity_ * sizeof(T)));
    for (std::size_t i = 0; i < other.size_; ++i) {
        new (array_ + i) T(other.array_[i]);
    }
    return *this;
}

template<typename T>
my_vector<T>::~my_vector() {
    clear();
    ::operator delete[](array_);
}

template<typename T>
std::size_t my_vector<T>::size() const {
    return size_;
}
    
template<typename T>    
std::size_t my_vector<T>::capacity() const {
    return capacity_;
}

template<typename T>
bool my_vector<T>::empty() const {
    return size_ == 0; 
}

template<typename T>
void my_vector<T>::reserve(std::size_t n) {
    if (n <= capacity_) {
        return;
    }

    std::size_t next_capacity = 1;
    while (next_capacity < n) {
        next_capacity <<= 1;
    }

    T* new_array = static_cast<T*>(::operator new[](next_capacity * sizeof(T)));

    for (std::size_t i = 0; i < size_; ++i) {
        new (new_array + i) T(std::move(array_[i]));
        array_[i].~T();
    }

    ::operator delete[](array_);

    array_ = new_array;
    capacity_ = next_capacity;
}



template<typename T>
void my_vector<T>::resize(std::size_t n) {
    if (n > size_) {
        if (std::is_default_constructible_v<T>) {
            if (n > capacity_) {
                reserve(n);
            }
            for (std::size_t i = size_; i < n; ++i) {
                new (array_ + i) T();
            }
        }
    } else if (n < size_) {
        for (std::size_t i = n; i < size_; ++i) {
            array_[i].~T();
        }
    }
    size_ = n;
}

template<typename T>
void my_vector<T>::pop_back() {
    assert(size_ > 0);
    if (size_ > 0) {
        size_--;
        array_[size_].~T();
    }
}

template<typename T>
void my_vector<T>::clear() {
    for (std::size_t i = 0; i < size_; i++) {
        array_[i].~T();
    }
    size_ = 0;
}

template<typename T>
void my_vector<T>::push_back(const T& meow) {
    if (size_ == capacity_) {
        size_t new_capacity = 0;
        if (capacity_ == 0) {
            new_capacity = 1;
            reserve(new_capacity);
        } else {
            new_capacity = capacity_ * 2;
            reserve(new_capacity);
        }
    }
    new (array_ + size_) T(meow);
    ++size_;
}

template<typename T>
T& my_vector<T>::operator[](std::size_t index) {
    return array_[index];
}

template<typename T>
const T& my_vector<T>::operator[](std::size_t index) const {
    return array_[index];
}

template <typename T>
void test_my_vector(const T& item1, const T& item2) {
    containers::my_vector<T> vec;
    
    vec.push_back(item1);
    vec.push_back(item2);
    
    std::cout << "Размер вектора после добавления 2 элементов: " << vec.size() << std::endl;

    std::cout << "Содержимое вектора: " << vec << std::endl;
    vec.pop_back();
    std::cout << "Размер вектора после pop_back(): " << vec.size() << std::endl;


    vec.pop_back();
    std::cout << "Размер вектора после второго pop_back(): " << vec.size() << std::endl;

    std::cout << "Вектор пустой: " << (vec.empty() ? "Да" : "Нет") << std::endl;


    vec.push_back(item1);
    vec.push_back(item2);
    std::cout << "Размер вектора после добавления элементов снова: " << vec.size() << std::endl;
    vec.clear();
    std::cout << "Размер вектора после clear(): " << vec.size() << std::endl;
}

template <typename T>
void test_my_vector_default_constructible() {
    std::cout << "Тестирование my_vector с типом: " << typeid(T).name() << std::endl;

    containers::my_vector<T> vec(5);
    std::cout << "Размер вектора после создания (с 5 элементами): " << vec.size() << std::endl;

    vec.push_back(T());
    std::cout << "Размер вектора после добавления нового элемента: " << vec.size() << std::endl;
    std::cout << "Последний элемент: " << vec[vec.size() - 1] << std::endl;

    vec.pop_back();
    std::cout << "Размер вектора после pop_back(): " << vec.size() << std::endl;

    std::size_t prev_capacity = vec.capacity();
    vec.reserve(prev_capacity * 2);
    std::cout << "Размер вектора после reserve: " << vec.size() << ", вместимость: " << vec.capacity() << std::endl;

    vec.clear();
    std::cout << "Размер вектора после clear(): " << vec.size() << std::endl;
    
    std::cout << "Вектор пустой: " << (vec.empty() ? "Да" : "Нет") << std::endl;

    containers::my_vector<T> vec_copy = vec;
    std::cout << "Размер вектора после копирования: " << vec_copy.size() << std::endl;

    containers::my_vector<T> vec_assign(3);
    vec_assign = vec_copy;
    std::cout << "Размер вектора после присваивания: " << vec_assign.size() << std::endl;
}


} //namespace containers
