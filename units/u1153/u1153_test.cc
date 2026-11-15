// FILE: u1153_test.cc
#include "gtest/gtest.h"
#include "ceres/context_impl.h"
#include "ceres/linear_operator.h"

// P1: START -> 1 -> END
TEST(RightMultiplyAndAccumulateTest, TC1_CallsTarget) {
  LinearOperator object{};
  Vector & x a0{};
  Vector & y a1{};
  int a3 = 0;
  object.RightMultiplyAndAccumulate(a0, a1, nullptr, a3);
}

