// Copyright (c) 2021, Jiang Yinzuo. All rights reserved.

#pragma once

#include <cstring>
#include <emmintrin.h>
#include "_base/matrix_base.h"

namespace libra {

template<typename T, std::size_t R, std::size_t C>
class Matrix : public MatrixBase<T, R, C> {

 public:
  explicit Matrix(const T(&list)[R][C]) {
    memcpy(this->data_, list, sizeof(T) * R * C);
  }

  Matrix() = default;

  template<std::size_t U>
  Matrix<T, R, U> operator*(Matrix<T, C, U> &mat) {
    Matrix<T, R, U> m{};
    for (int i = 0; i < R; ++i) {
      for (int j = 0; j < U; ++j) {
        for (int k = 0; k < C; ++k) {
          m[i][j] += this->data_[i][k] * mat[k][j];
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
        this->data_[i][j] *= num;
      }
    }
    return *this;
  }

};

template<std::size_t R, std::size_t C>
class Matrix<float, R, C> : public MatrixBase<float, R, C> {
 public:
  explicit Matrix(const float (&list)[R][C]) {
    memcpy(this->data_, list, sizeof(float) * R * C);
  }

  Matrix() = default;

  Matrix<float, R, C> &operator*=(float num) {
#ifdef BLAS_USE_SSE2
    const __m128 scalar = _mm_set1_ps(num);
    for (int i = 0; i < R; ++i) {
      for (int j = 0; j + 4 <= C; j += 4) {
        __m128 res = _mm_mul_ps(_mm_set_ps(this->data_[i][j + 3],
                                           this->data_[i][j + 2],
                                           this->data_[i][j + 1],
                                           this->data_[i][j]), scalar);
        memcpy(&this->data_[i][j], &res, sizeof(res));
      }
      switch (C % 4) {
        case 3:this->data_[i][C - 3] *= num;
        case 2:this->data_[i][C - 2] *= num;
        case 1:this->data_[i][C - 1] *= num;
      }
    }
#else
    for (int i = 0; i < R; ++i) {
      for (int j = 0; j < C; ++j) {
        this->data_[i][j] *= num;
      }
    }
#endif
    return *this;
  }

  Matrix<float, R, C> &operator+=(float num) {
#ifdef BLAS_USE_SSE2
    const __m128 scalar = _mm_set1_ps(num);
    for (int i = 0; i < R; ++i) {
      for (int j = 0; j + 4 <= C; j += 4) {
        __m128 res = _mm_add_ps(_mm_set_ps(this->data_[i][j + 3],
                                           this->data_[i][j + 2],
                                           this->data_[i][j + 1],
                                           this->data_[i][j]), scalar);
        memcpy(&this->data_[i][j], &res, sizeof(res));
      }
      switch (C % 4) {
        case 3:this->data_[i][C - 3] += num;
        case 2:this->data_[i][C - 2] += num;
        case 1:this->data_[i][C - 1] += num;
      }
    }
#else
    for (int i = 0; i < R; ++i) {
      for (int j = 0; j < C; ++j) {
        this->data_[i][j] += num;
      }
    }
#endif
    return *this;
  }

};

}
