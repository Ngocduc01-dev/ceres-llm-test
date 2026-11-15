// FILE: u1009_test.cc
#include "gtest/gtest.h"
#include "ceres/low_rank_inverse_hessian.h"

// P1: START -> 1 -> END
TEST(LeftMultiplyAndAccumulateTest, TC1_CallsTarget) {
  LowRankInverseHessian object{};
  double a0[5] = {};
  double a1[5] = {};
  object.LeftMultiplyAndAccumulate(a0, a1);
}

