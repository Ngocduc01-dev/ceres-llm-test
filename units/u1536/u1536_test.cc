// FILE: u1536_test.cc
#include "gtest/gtest.h"
#include "ceres/problem.h"
#include "ceres/solver.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1536, TC1_CallsTarget) {
  Solver::Options options{};
  ceres::Solve(options, nullptr, nullptr);
}
