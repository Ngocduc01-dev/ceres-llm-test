// FILE: u1333_test.cc
#include "gtest/gtest.h"
#include "ceres/problem.h"

// P1: START -> 1 -> END
TEST(u1333_Test, TC1_CallsTarget) {
  ceres::Problem target{};
  target.SetParameterUpperBound(nullptr, nullptr, nullptr);
}
