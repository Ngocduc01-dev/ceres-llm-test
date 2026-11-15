// FILE: u1070_test.cc
#include "gtest/gtest.h"
#include "ceres/block_random_access_dense_matrix.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1070, TC1_CallsTarget) {
  ceres::internal::BlockRandomAccessDenseMatrix object{};
  object.SetZero();
}
