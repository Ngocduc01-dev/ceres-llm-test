// FILE: u0765_test.cc
#include "gtest/gtest.h"
#include "ceres/low_rank_inverse_hessian.h"

// P1: START -> 1 -> END
TEST(UpdateTest, TC1_CallsTarget) {
  LowRankInverseHessian object{};
  Vector & delta_x a0{};
  Vector & delta_gradient a1{};
  object.Update(a0, a1);
}

// P2: START -> 1 -> END
TEST(UpdateTest, TC2_CallsTarget) {
  LowRankInverseHessian object{};
  Vector & delta_x a0{};
  Vector & delta_gradient a1{};
  object.Update(a0, a1);
}

// P3: START -> 1 -> END
TEST(UpdateTest, TC3_CallsTarget) {
  LowRankInverseHessian object{};
  Vector & delta_x a0{};
  Vector & delta_gradient a1{};
  object.Update(a0, a1);
}

