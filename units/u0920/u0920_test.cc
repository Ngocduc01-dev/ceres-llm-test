// FILE: u0920_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"

// P1: START -> 1 -> END
TEST(RightMultiplyByPlusJacobianTest, TC1_CallsTarget) {
  Manifold object{};
  double a0[5] = {};
  int a1 = 0;
  double a2[5] = {};
  double a3[5] = {};
  object.RightMultiplyByPlusJacobian(a0, a1, a2, a3);
}

// P2: START -> 1 -> END
TEST(RightMultiplyByPlusJacobianTest, TC2_CallsTarget) {
  Manifold object{};
  double a0[5] = {};
  int a1 = 0;
  double a2[5] = {};
  double a3[5] = {};
  object.RightMultiplyByPlusJacobian(a0, a1, a2, a3);
}

// P3: START -> 1 -> END
TEST(RightMultiplyByPlusJacobianTest, TC3_CallsTarget) {
  Manifold object{};
  double a0[5] = {};
  int a1 = 0;
  double a2[5] = {};
  double a3[5] = {};
  object.RightMultiplyByPlusJacobian(a0, a1, a2, a3);
}

