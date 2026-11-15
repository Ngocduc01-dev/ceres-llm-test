// FILE: u1511_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"
#include "ceres/problem.h"

// P1: START -> 1 -> END
TEST(u1511_Test, TC1_CallsTarget) {
  ceres::Problem target{};
  target.SetManifold(nullptr, nullptr);
}
