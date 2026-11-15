// FILE: u1087_test.cc
#include "gtest/gtest.h"
#include "ceres/dense_cholesky.h"
#include "ceres/iterative_refiner.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1087, TC1_CallsTarget) {
  const int num_cols{};
  ceres::internal::DenseIterativeRefiner object{};
  object.Refine(num_cols, nullptr, nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1087, TC2_CallsTarget) {
  const int num_cols{};
  ceres::internal::DenseIterativeRefiner object{};
  object.Refine(num_cols, nullptr, nullptr, nullptr, nullptr);
}
