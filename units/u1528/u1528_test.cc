// FILE: u1528_test.cc
#include "gtest/gtest.h"
#include "ceres/problem.h"

// P1: START -> 1 -> END
TEST(u1528_Test, TC1_CallsTarget) {
  ceres::Problem target{};
  target.RemoveParameterBlock(nullptr);
}
