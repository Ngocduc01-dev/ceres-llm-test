// FILE: u1540_test.cc
#include "gtest/gtest.h"
#include "ceres/covariance.h"
#include "ceres/problem.h"

// P1: START -> 1 -> END
TEST(u1540_Test, TC1_CallsTarget) {
  ceres::Covariance target{};
  target.Compute(nullptr, nullptr);
}
