// FILE: u1054_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"

// P1: START -> 1 -> END
TEST(PlusJacobianTest, TC1_CallsTarget) {
  SubsetManifold object{};
  double a0[5] = {};
  double a1[5] = {};
  object.PlusJacobian(a0, a1);
}

// P2: START -> 1 -> END
TEST(PlusJacobianTest, TC2_CallsTarget) {
  SubsetManifold object{};
  double a0[5] = {};
  double a1[5] = {};
  object.PlusJacobian(a0, a1);
}

// P3: START -> 1 -> END
TEST(PlusJacobianTest, TC3_CallsTarget) {
  SubsetManifold object{};
  double a0[5] = {};
  double a1[5] = {};
  object.PlusJacobian(a0, a1);
}

