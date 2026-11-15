// FILE: u1154_test.cc
#include "gtest/gtest.h"
#include "ceres/context_impl.h"
#include "ceres/linear_operator.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1154, TC1_CallsTarget) {
  Vector x{};
  Vector y{};
  int num_threads{};
  ceres::internal::LinearOperator object{};
  object.LeftMultiplyAndAccumulate(x, y, nullptr, num_threads);
}
