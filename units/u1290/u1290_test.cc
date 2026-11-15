// FILE: u1290_test.cc
#include "gtest/gtest.h"
#include "ceres/sparse_cholesky.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1290, TC1_CallsTarget) {
  ceres::internal::RefinedSparseCholesky object{};
  object.Solve(nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1290, TC2_CallsTarget) {
  ceres::internal::RefinedSparseCholesky object{};
  object.Solve(nullptr, nullptr, nullptr);
}
