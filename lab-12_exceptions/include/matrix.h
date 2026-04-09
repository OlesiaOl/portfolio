#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <iostream>
#include <stdexcept>
#include <string>

namespace math {

class Matrix {
private:
    std::size_t m_rows = 0;
    std::size_t m_columns = 0;
    std::vector<std::vector<int>> m_data;
public:
    Matrix() = default;
    Matrix(std::size_t rows, std::size_t columns);
    friend std::ostream& operator<<(std::ostream& os, const Matrix& matrix);
    friend std::istream& operator>>(std::istream& is, Matrix& matrix);
    Matrix& operator+=(const Matrix& other);
    Matrix& operator*=(const Matrix& other);
    std::size_t get_rows() const;
    std::size_t get_columns() const;
    void set(std::size_t row, std::size_t column, int value);
    int get(std::size_t row, std::size_t column) const;
};

class MatrixException : public std::exception {
protected:
    std::string m_message;
public:
    explicit MatrixException(const std::string& message) : m_message(message) {}
    const char* what() const noexcept override {
        return m_message.c_str();
    }
};

} // namespace math

#endif // MATRIX_H
