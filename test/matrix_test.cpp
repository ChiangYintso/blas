// Copyright (c) 2021, Jiang Yinzuo. All rights reserved.

#include "gtest/gtest.h"
#include <blas/matrix.h>

namespace {

TEST(MatrixTest, ScalarOperation) {
  blas::Matrix<float, 4, 3> mat{};
  mat += 4;
  for (auto &row : mat) {
    for (float e : row) {
      ASSERT_EQ(e, 4.0);
    }
  }
  mat[3][0] = 2.0;
  ASSERT_EQ(mat[3][0], 2.0);
  mat *= 1.1;
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 3; ++j) {
      if (i == 3 && j == 0) {
        ASSERT_TRUE(abs(mat[i][j] - 2.2) < 1e-6);
      } else {
        ASSERT_TRUE(abs(mat[i][j] - 4.4) < 1e-6);
      }
    }
  }
}

}