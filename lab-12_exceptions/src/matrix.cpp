#include <vector>
#include <iostream>
#include <fstream>

#include "matrix.h"

namespace math {

Matrix::Matrix(std::size_t rows, std::size_t columns) 
    : m_rows(rows), m_columns(columns), m_data(rows, std::vector<int>(columns)) {}

std::ostream& operator<<(std::ostream& os, const Matrix& matrix) {
    for (std::size_t i = 0; i < matrix.m_rows; i++) {
        for (std::size_t j = 0; j < matrix.m_columns; j++) {
            os << matrix.m_data[i][j];
            if (j + 1 < matrix.m_columns) {
                os << " ";
            }
        }
        os << "\n";
    }
    return os;
}

Matrix& Matrix::operator+=(const Matrix& other) {
    if (m_rows != other.m_rows || m_columns != other.m_columns) {
        throw MatrixException("ADD: dimensions do not match.");
    }
    for (std::size_t i = 0; i < m_rows; ++i) {
        for (std::size_t j = 0; j < m_columns; j++) {
            m_data[i][j] += other.m_data[i][j];
        }
    }
    return *this;
}

std::size_t Matrix::get_rows() const { return m_rows; }

std::size_t Matrix::get_columns() const { return m_columns; }

void Matrix::set(std::size_t row, std::size_t column, int value) {
    if (row >= m_rows || column >= m_columns) {
        throw MatrixException("GET: bad index.");
    }
    m_data[row][column] = value;
}

int Matrix::get(std::size_t row, std::size_t column) const {
    if (row >= m_rows || column >= m_columns) {
        throw MatrixException("ACCESS: bad index.");
    }
    return m_data[row][column];
}

Matrix& Matrix::operator*=(const Matrix& other) {
    if (m_columns != other.m_rows) {
        throw MatrixException("MUL: #arg1.columns != #arg2.rows.");
    }
    Matrix multiplied(m_rows, other.m_columns);

    for (std::size_t i = 0; i < m_rows; i++) {
        for (std::size_t j = 0; j < other.m_columns; j++) {
            int elemSum = 0;
            for (std::size_t cur = 0; cur < m_columns; cur++) {
                elemSum += m_data[i][cur] * other.m_data[cur][j];
            }
            multiplied.set(i, j, elemSum);
        }
    }

    *this = std::move(multiplied);
    return *this;
}

std::istream& operator>>(std::istream& is, Matrix& matrix) {
    std::size_t rows, columns;
    if (!(is >> rows >> columns) || rows == 0 || columns == 0) {
        throw MatrixException("LOAD: invalid file format.");
    }

    Matrix temp(rows, columns);
    for (std::size_t i = 0; i < rows; ++i) {
        for (std::size_t j = 0; j < columns; ++j) {
            if (!(is >> temp.m_data[i][j])) {
                throw MatrixException("LOAD: invalid file format.");
            }
        }
    }
    matrix = std::move(temp);
    return is;
}

} // namespace math
