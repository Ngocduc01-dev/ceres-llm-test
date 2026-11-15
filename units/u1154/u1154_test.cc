// FILE: u1154_test.cc
#include "gtest/gtest.h"
#include "ceres/context_impl.h"
#include "ceres/linear_operator.h"

// P1: START -> 1 -> END
TEST(LeftMultiplyAndAccumulateTest, TC1_CallsTarget) {
  LinearOperator object{};
  Vector & x a0{};
  Vector & y a1{};
  int a3 = 0;
  object.LeftMultiplyAndAccumulate(a0, a1, nullptr, a3);
}

