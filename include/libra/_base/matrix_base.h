// Copyright (c) 2021, Jiang Yinzuo. All rights reserved.

#pragma once
#include <concepts>

template<typename T>
concept number = std::integral<T> || std::floating_point<T>;

namespace libra {
template<number T, std::size_t R, std::size_t C>
class MatrixBase {
 public:

  T *operator[](std::size_t idx) {
    return &this->data_[idx][0];
  }

  auto begin() -> T (*)[C] {
    return &data_[0];
  }

  auto end() -> T (*)[C] {
    return &data_[R];
  }

 protected:
  T data_[R][C];
};
}