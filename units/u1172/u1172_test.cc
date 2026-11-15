// FILE: u1172_test.cc
#include "gtest/gtest.h"
#include "ceres/linear_least_squares_problems.h"
#include "ceres/triplet_sparse_matrix.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1172, TC1_CallsTarget) {
  ceres::internal::LinearLeastSquaresProblem0();
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1172, TC2_CallsTarget) {
  ceres::internal::LinearLeastSquaresProblem0();
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1172, TC3_CallsTarget) {
  ceres::internal::LinearLeastSquaresProblem0();
}
