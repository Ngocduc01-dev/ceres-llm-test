// FILE: u1173_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/block_structure.h"
#include "ceres/linear_least_squares_problems.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1173, TC1_CallsTarget) {
  ceres::internal::LinearLeastSquaresProblem4();
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1173, TC2_CallsTarget) {
  ceres::internal::LinearLeastSquaresProblem4();
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1173, TC3_CallsTarget) {
  ceres::internal::LinearLeastSquaresProblem4();
}
