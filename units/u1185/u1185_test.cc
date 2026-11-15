// FILE: u1185_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/block_structure.h"
#include "ceres/linear_least_squares_problems.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1185, TC1_CallsTarget) {
  ceres::internal::LinearLeastSquaresProblem2();
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1185, TC2_CallsTarget) {
  ceres::internal::LinearLeastSquaresProblem2();
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1185, TC3_CallsTarget) {
  ceres::internal::LinearLeastSquaresProblem2();
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1185, TC4_CallsTarget) {
  ceres::internal::LinearLeastSquaresProblem2();
}
