// FILE: u0937_test.cc
#include "gtest/gtest.h"
#include "ceres/context_impl.h"
#include "ceres/linear_operator.h"

// P1: START -> 1 -> END
TEST(RightMultiplyAndAccumulateTest, TC1_CallsTarget) {
  LinearOperator object{};
  double a0[5] = {};
  double a1[5] = {};
  int a3 = 0;
  object.RightMultiplyAndAccumulate(a0, a1, nullptr, a3);
}

// P2: START -> 1 -> END
TEST(RightMultiplyAndAccumulateTest, TC2_CallsTarget) {
  LinearOperator object{};
  double a0[5] = {};
  double a1[5] = {};
  int a3 = 0;
  object.RightMultiplyAndAccumulate(a0, a1, nullptr, a3);
}

