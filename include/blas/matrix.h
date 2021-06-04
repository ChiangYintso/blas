#pragma once

#include <cstring>

namespace blas {
template<typename T, std::size_t R, std::size_t C>
class Matrix {

 public:
  explicit Matrix(const T(&list)[R][C]) {
    memcpy(data_, list, sizeof(T) * R * C);
  }

  Matrix() = default;
  T *operator[](std::size_t idx) {
    return &data_[idx][0];
  }

  template<std::size_t U>
  Matrix<T, R, U> operator*(Matrix<T, C, U> &mat) {
    Matrix<T, R, U> m{};
    for (int i = 0; i < R; ++i) {
      for (int j = 0; j < U; ++j) {
        for (int k = 0; k < C; ++k) {
          m[i][j] += data_[i][k] * mat[k][j];
        }
      }
    }
    return m;
  }


  Matrix<T, R, C> operator*(T num) {
    Matrix<T, R, C> m = *this;
     for (int i = 0; i < R; ++i) {
       for (int j = 0; j < C; ++j) {
         m[i][j] *= num;
       }
     }
    return m;
  }

  Matrix<T, R, C> &operator*=(T num) {
    for (int i = 0; i < R; ++i) {
      for (int j = 0; j < C; ++j) {
        data_[i][j] *= num;
      }
    }
    return *this;
  }

  T *begin() {
    return &data_[0][0];
  }

  T *end() {
    return &data_[R - 1][C];
  }

 private:
  T data_[R][C];
};

}
