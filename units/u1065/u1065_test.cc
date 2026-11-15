// FILE: u1065_test.cc
#include "gtest/gtest.h"
#include "ceres/problem_impl.h"
#include "ceres/problem_impl.cc"

// P1: START -> 1 -> END
TEST(CheckForNoAliasingTest, TC1_CallsTarget) {
  double a0[5] = {};
  int a1 = 0;
  double a2[5] = {};
  int a3 = 0;
  CheckForNoAliasing(a0, a1, a2, a3);
}

