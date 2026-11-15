// FILE: u1050_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"

// P1: START -> 1 -> END
TEST(PlusTest, TC1_CallsTarget) {
  SubsetManifold object{};
  double a0[5] = {};
  double a1[5] = {};
  double a2[5] = {};
  object.Plus(a0, a1, a2);
}

// P2: START -> 1 -> END
TEST(PlusTest, TC2_CallsTarget) {
  SubsetManifold object{};
  double a0[5] = {};
  double a1[5] = {};
  double a2[5] = {};
  object.Plus(a0, a1, a2);
}

// P3: START -> 1 -> END
TEST(PlusTest, TC3_CallsTarget) {
  SubsetManifold object{};
  double a0[5] = {};
  double a1[5] = {};
  double a2[5] = {};
  object.Plus(a0, a1, a2);
}

