// FILE: u1128_test.cc
#include "gtest/gtest.h"
#include "ceres/tiny_solver.h"

// P1: START -> 1 -> END
TEST(SolveTest, TC1_CallsTarget) {
  TinySolver object{};
  Function & function a0{};
  object.Solve(a0, nullptr);
}

