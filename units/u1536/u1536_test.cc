// FILE: u1536_test.cc
#include "gtest/gtest.h"
#include "ceres/problem.h"
#include "ceres/solver.h"

// P1: START -> 1 -> END
TEST(u1536_Test, TC1_CallsTarget) {
  Solve(nullptr, nullptr, nullptr);
}
