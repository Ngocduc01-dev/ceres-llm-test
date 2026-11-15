// FILE: u0858_test.cc
#include "gtest/gtest.h"
#include "ceres/evaluator.h"
#include "ceres/sparse_matrix.h"

// P1: START -> 1 -> END
TEST(EvaluateTest, TC1_CallsTarget) {
  Evaluator object{};
  double a0[5] = {};
  double a1[5] = {};
  double a2[5] = {};
  double a3[5] = {};
  object.Evaluate(a0, a1, a2, a3, nullptr);
}

