// FILE: u1512_test.cc
#include "gtest/gtest.h"
#include "ceres/crs_matrix.h"
#include "ceres/problem.h"

// P1: START -> 1 -> END
TEST(u1512_Test, TC1_CallsTarget) {
  ceres::Problem target{};
  target.Evaluate(nullptr, nullptr, nullptr, nullptr, nullptr);
}
