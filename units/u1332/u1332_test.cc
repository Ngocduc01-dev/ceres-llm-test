// FILE: u1332_test.cc
#include "gtest/gtest.h"
#include "ceres/problem.h"

// P1: START -> 1 -> END
TEST(u1332_Test, TC1_CallsTarget) {
  ceres::Problem target{};
  target.SetParameterLowerBound(nullptr, nullptr, nullptr);
}
