#ifndef MY_VECTOR_H_
#define MY_VECTOR_H_

#include <iostream>
#include <memory>
#include <type_traits>
#include <cstddef>

namespace containers {

template<typename T>
class my_vector {
public:
    my_vector();
    my_vector(std::size_t n);
    my_vector(const my_vector& other);
    my_vector<T>& operator=(const my_vector other);
    ~my_vector();

    std::size_t size() const;
    std::size_t capacity() const;
    bool empty() const;

    void resize(std::size_t n);
    void reserve(std::size_t n);

    T& operator[](std::size_t index);
    const T& operator[](std::size_t index) const;

    friend std::ostream& operator<<(std::ostream& os, const my_vector<T>& vec) {
        for (std::size_t i = 0; i < vec.size(); ++i) {
            os << vec.array_[i];
            if (!vec.empty() && i != vec.size() - 1) {
                os << " ";
            }
        }
        return os;
    }

    std::size_t calculate_capacity(std::size_t n) const;

    void push_back(const T& value);
    void pop_back();
    void clear();

private:
    static const size_t INITIAL_CAPACITY = 1;
    size_t capacity_;
    size_t size_;
    T* array_;
};


} // namespace containers



#include "my_vector_impl.hpp"

#endif  // MY_VECTOR_H_
