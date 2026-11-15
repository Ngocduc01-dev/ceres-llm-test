// FILE: u1438_test.cc
#include "gtest/gtest.h"
#include "ceres/linear_least_squares_problems.h"
#include "ceres/sparse_matrix.h"

// P1: START -> 1 -> END
TEST(u1438_Test, TC1_CallsTarget) {
  DumpLinearLeastSquaresProblem(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
}
