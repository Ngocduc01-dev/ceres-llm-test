// FILE: u1128_test.cc
#include "gtest/gtest.h"
#include "ceres/tiny_solver.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1128, TC1_CallsTarget) {
  Function function{};
  ceres::TinySolver object{};
  object.Solve(function, nullptr);
}
