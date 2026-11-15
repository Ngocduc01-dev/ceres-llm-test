// FILE: u1391_test.cc
#include "gtest/gtest.h"
#include "ceres/linear_least_squares_problems.h"

// P1: START -> 1 -> END
TEST(u1391_Test, TC1_CallsTarget) {
  CreateLinearLeastSquaresProblemFromId(nullptr);
}
