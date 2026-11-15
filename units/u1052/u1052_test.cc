// FILE: u1052_test.cc
#include "gtest/gtest.h"
#include "ceres/cost_function.h"
#include "ceres/normal_prior.h"

// P1: START -> 1 -> END
TEST(EvaluateTest, TC1_CallsTarget) {
  NormalPrior object{};
  double a0[5] = {};
  double a1[5] = {};
  double a2[5] = {};
  object.Evaluate(a0, a1, a2);
}

// P2: START -> 1 -> END
TEST(EvaluateTest, TC2_CallsTarget) {
  NormalPrior object{};
  double a0[5] = {};
  double a1[5] = {};
  double a2[5] = {};
  object.Evaluate(a0, a1, a2);
}

