// FILE: u1511_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"
#include "ceres/problem.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1511, TC1_CallsTarget) {
  ceres::Problem object{};
  object.SetManifold(nullptr, nullptr);
}
