// FILE: u1538_test.cc
#include "gtest/gtest.h"
#include "ceres/gradient_problem.h"
#include "ceres/gradient_problem_solver.h"

// P1: START -> 1 -> END
TEST(u1538_Test, TC1_CallsTarget) {
  Solve(nullptr, nullptr, nullptr, nullptr);
}
