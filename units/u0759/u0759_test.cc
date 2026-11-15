// FILE: u0759_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/numeric_diff.h"

// P1: START -> 1 -> END
TEST(EvaluateJacobianColumnTest, TC1_CallsTarget) {
  NumericDiff object{};
  int a1 = 0;
  double a2 = 0.0;
  int a3 = 0;
  int a4 = 0;
  double a5[5] = {};
  double a6[5] = {};
  double a7[5] = {};
  double a8[5] = {};
  double a9[5] = {};
  double a10[5] = {};
  object.EvaluateJacobianColumn(nullptr, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
}

// P2: START -> 1 -> END
TEST(EvaluateJacobianColumnTest, TC2_CallsTarget) {
  NumericDiff object{};
  int a1 = 0;
  double a2 = 0.0;
  int a3 = 0;
  int a4 = 0;
  double a5[5] = {};
  double a6[5] = {};
  double a7[5] = {};
  double a8[5] = {};
  double a9[5] = {};
  double a10[5] = {};
  object.EvaluateJacobianColumn(nullptr, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
}

// P3: START -> 1 -> END
TEST(EvaluateJacobianColumnTest, TC3_CallsTarget) {
  NumericDiff object{};
  int a1 = 0;
  double a2 = 0.0;
  int a3 = 0;
  int a4 = 0;
  double a5[5] = {};
  double a6[5] = {};
  double a7[5] = {};
  double a8[5] = {};
  double a9[5] = {};
  double a10[5] = {};
  object.EvaluateJacobianColumn(nullptr, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10);
}

