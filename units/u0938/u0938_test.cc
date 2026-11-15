// FILE: u0938_test.cc
#include "gtest/gtest.h"
#include "ceres/context_impl.h"
#include "ceres/linear_operator.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0938, TC1_CallsTarget) {
  int num_threads{};
  ceres::internal::LinearOperator object{};
  object.LeftMultiplyAndAccumulate(nullptr, nullptr, nullptr, num_threads);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u0938, TC2_CallsTarget) {
  int num_threads{};
  ceres::internal::LinearOperator object{};
  object.LeftMultiplyAndAccumulate(nullptr, nullptr, nullptr, num_threads);
}
