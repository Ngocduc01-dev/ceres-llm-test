// FILE: u1070_test.cc
#include "gtest/gtest.h"
#include "ceres/block_random_access_dense_matrix.h"

// P1: START -> 1 -> END
TEST(SetZeroTest, TC1_CallsTarget) {
  BlockRandomAccessDenseMatrix object{};
  object.SetZero();
}

