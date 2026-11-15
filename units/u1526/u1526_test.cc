// FILE: u1526_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"
#include "ceres/problem.h"

// P1: START -> 1 -> END
TEST(u1526_Test, TC1_CallsTarget) {
  ceres::Problem target{};
  target.AddParameterBlock(nullptr, nullptr, nullptr);
}
