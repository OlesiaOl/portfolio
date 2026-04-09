#include <algorithm>
#include <iostream>
#include "matrix.hpp"

Matrix::Matrix(std::size_t r, std::size_t c):_rows(r), _cols(c), _data(new int*[r]) {
  for (std::size_t i = 0; i < r; i++) {
    _data[i] = new int[c]();
  }
}

Matrix::~Matrix() {
  for (std::size_t i = 0; i < _rows; i++) {
    delete[] _data[i];
  }
  delete[] _data;
}

Matrix::Matrix(const Matrix& m) : Matrix(m._rows, m._cols) {
  for (std::size_t i = 0; i < m._rows; i++) {
    for (std::size_t j = 0; j < m._cols; j++) {
      set(i, j, m.get(i, j)); 
    }
  }
}

Matrix& Matrix::operator=(const Matrix& m) {
  if (this == &m) {
    return *this;
  }
  for (std::size_t i = 0; i < _rows; i++){
    delete[] _data[i];
  }

  delete[] _data;

  _rows = m._rows;
  _cols = m._cols;
  _data = new int*[_rows];
  for (std::size_t i = 0; i < _rows; i++) {
    _data[i] = new int[_cols];
  }

  for (std::size_t i = 0; i < _rows; i++) {
    for (std::size_t j = 0; j < _cols; j++) {
      set(i, j, m.get(i, j)); 
    }
  }
  return *this;
}

std::size_t Matrix::get_rows() const { return _rows; }

std::size_t Matrix::get_cols() const { return _cols; }

void Matrix::set(std::size_t i, std::size_t j, int val) {
  _data[i][j] = val;
}

int Matrix::get(std::size_t i, std::size_t j) const {
  return _data[i][j];
}
/*
void Matrix::print(FILE* f) {
  for (std::size_t i = 0; i < _rows; i++) {
    for (std::size_t j = 0; j < _cols; j++) {
      fprintf(f, "%d", _data[i][j]);
      if (j < _cols - 1) {
        fprintf(f, " ");
      }
    }
    fprintf(f, "\n");
  }
}
*/
bool operator==(const Matrix& m1, const Matrix& m2) {
    if (m1._rows != m2._rows || m1._cols != m2._cols) {
        return false;
    }

    for (std::size_t i = 0; i < m1._rows; i++) {
        if (!std::equal(m1._data[i], m1._data[i] + m1._cols, m2._data[i])) {
            return false;
        }
    }
    return true;
}

bool operator!=(const Matrix& m1, const Matrix& m2) {
    return !(m1 == m2);
}
/*
Matrix& Matrix::operator+=(const Matrix& m) {
  for ( std::size_t i = 0; i < _rows; i++) {
    for (std::size_t j = 0; j < _cols; j++) {
      _data[i][j] = m._data[i][j] + _data[i][j];
    }
  }
  return *this;
}

Matrix& Matrix::operator-=(const Matrix& m) {
  for ( std::size_t i = 0; i < _rows; i++) {
    for (std::size_t j = 0; j < _cols; j++) {
      _data[i][j] = _data[i][j] - m.get(i, j);
    }
  }
  return *this;
}

Matrix& Matrix::operator*=(const Matrix& m) {
  Matrix multiplied(_rows, m.get_cols());

  for (std::size_t i = 0; i < _rows; i++) {
    for (std::size_t j = 0; j < m.get_cols(); j++) {
      int elemSum = 0;
      for (std::size_t cur = 0; cur < _cols; cur++) {
        elemSum += _data[i][cur] * m._data[cur][j];
      }
      multiplied.set(i, j, elemSum);
    }
  }
  if (_rows != multiplied.get_rows() || _cols != multiplied.get_cols()) {
    *this = multiplied;
  } else {
    for (std::size_t i = 0; i < _rows; i++) {
      for (std::size_t j = 0; j < _cols; j++) {
        _data[i][j] = multiplied.get(i, j);
      }
    }
  }
  return *this;
}

Matrix Matrix::operator+(const Matrix& m) const {
  Matrix buffMatrix(_rows, _cols);
  for (std::size_t i = 0; i < _rows; i++) {
    for (std::size_t j = 0; j < _cols; j++) {
      buffMatrix._data[i][j] = _data[i][j] + m._data[i][j];
    }
  }
  return buffMatrix;
}

Matrix Matrix::operator-(const Matrix& m) const {
  Matrix buffMatrix(this->_rows, this->_cols);
  for(std::size_t i = 0; i < this->_rows; i++) {
    for(std::size_t j = 0; j < this->_cols; j++) {
      buffMatrix.set(i, j, this->get(i, j) - m.get(i, j));
    }
  }
  return buffMatrix;
}

Matrix Matrix::operator*(const Matrix& m) const{
  Matrix multiplied(_rows, m.get_cols());
  for (std::size_t i = 0; i < _rows; i++) {
    for (std::size_t j = 0; j < m.get_cols(); j++) {
      int elemSum = 0;
      for (std::size_t cur = 0; cur < _cols; cur++) {
        elemSum+=_data[i][cur] * m.get(cur, j);
      }
      multiplied.set(i, j, elemSum);
    }
  }
  return multiplied;
}
*/