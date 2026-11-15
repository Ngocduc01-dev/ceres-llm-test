// FILE: u1075_test.cc
#include "gtest/gtest.h"
#include "ceres/dense_sparse_matrix.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1075, TC1_CallsTarget) {
  ceres::internal::DenseSparseMatrix object{};
  object.LeftMultiplyAndAccumulate(nullptr, nullptr);
}
