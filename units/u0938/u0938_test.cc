// FILE: u0938_test.cc
#include "gtest/gtest.h"
#include "ceres/context_impl.h"
#include "ceres/linear_operator.h"

// P1: START -> 1 -> END
TEST(LeftMultiplyAndAccumulateTest, TC1_CallsTarget) {
  LinearOperator object{};
  double a0[5] = {};
  double a1[5] = {};
  int a3 = 0;
  object.LeftMultiplyAndAccumulate(a0, a1, nullptr, a3);
}

// P2: START -> 1 -> END
TEST(LeftMultiplyAndAccumulateTest, TC2_CallsTarget) {
  LinearOperator object{};
  double a0[5] = {};
  double a1[5] = {};
  int a3 = 0;
  object.LeftMultiplyAndAccumulate(a0, a1, nullptr, a3);
}

