// FILE: u1331_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"
#include "ceres/problem.h"

// P1: START -> 1 -> END
TEST(u1331_Test, TC1_CallsTarget) {
  ceres::Problem target{};
  target.GetManifold(nullptr);
}
