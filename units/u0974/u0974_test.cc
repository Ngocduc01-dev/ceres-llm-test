// FILE: u0974_test.cc
#include "gtest/gtest.h"
#include "ceres/linear_least_squares_problems.h"
#include "ceres/sparse_matrix.h"
#include "ceres/linear_least_squares_problems.cc"

// P1: START -> 1 -> END
TEST(DumpLinearLeastSquaresProblemToConsoleTest, TC1_CallsTarget) {
  double a1[5] = {};
  double a2[5] = {};
  double a3[5] = {};
  i a4{};
  DumpLinearLeastSquaresProblemToConsole(nullptr, a1, a2, a3, a4);
}

// P2: START -> 1 -> END
TEST(DumpLinearLeastSquaresProblemToConsoleTest, TC2_CallsTarget) {
  double a1[5] = {};
  double a2[5] = {};
  double a3[5] = {};
  i a4{};
  DumpLinearLeastSquaresProblemToConsole(nullptr, a1, a2, a3, a4);
}

// P3: START -> 1 -> END
TEST(DumpLinearLeastSquaresProblemToConsoleTest, TC3_CallsTarget) {
  double a1[5] = {};
  double a2[5] = {};
  double a3[5] = {};
  i a4{};
  DumpLinearLeastSquaresProblemToConsole(nullptr, a1, a2, a3, a4);
}

