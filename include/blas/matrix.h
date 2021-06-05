#pragma once

#include <cstring>
#include <emmintrin.h>

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

  auto begin() -> T (*)[C] {
    return &data_[0];
  }

  auto end() -> T (*)[C] {
    return &data_[R - 1];
  }

 private:
  T data_[R][C];
};

template<std::size_t R, std::size_t C>
class Matrix<float, R, C> {
 public:
  explicit Matrix(const float (&list)[R][C]) {
    memcpy(data_, list, sizeof(float) * R * C);
  }

  Matrix() = default;
  float *operator[](std::size_t idx) {
    return &data_[idx][0];
  }

  Matrix<float, R, C> &operator*=(float num) {
    const __m128 scalar = _mm_set1_ps(num);
    for (int i = 0; i < R; ++i) {
      for (int j = 0; j < R; j += 4) {
        __m128 res = _mm_mul_ps(_mm_set_ps(data_[i][j + 3], data_[i][j + 2], data_[i][j + 1], data_[i][j]), scalar);
        memcpy(&data_[i][j], &res, sizeof(res));
      }
      switch (C % 4) {
        case 3:data_[i][C - 3] *= num;
        case 2:data_[i][C - 2] *= num;
        case 1:data_[i][C - 1] *= num;
      }
    }
    return *this;
  }

  Matrix<float, R, C> &operator+=(float num) {
    const __m128 scalar = _mm_set1_ps(num);
    for (int i = 0; i < R; ++i) {
      for (int j = 0; j < R; j += 4) {
        __m128 res = _mm_add_ps(_mm_set_ps(data_[i][j + 3], data_[i][j + 2], data_[i][j + 1], data_[i][j]), scalar);
        memcpy(&data_[i][j], &res, sizeof(res));
      }
      switch (C % 4) {
        case 3:data_[i][C - 3] += num;
        case 2:data_[i][C - 2] += num;
        case 1:data_[i][C - 1] += num;
      }
    }
    return *this;
  }

  auto begin() -> float (*)[C] {
    return &data_[0];
  }

  auto end() -> float (*)[C] {
    return &data_[R - 1];
  }

 private:
  float data_[R][C];

};

}
