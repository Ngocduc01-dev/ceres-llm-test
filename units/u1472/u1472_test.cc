// FILE: u1472_test.cc
#include "gtest/gtest.h"
#include "ceres/solver.h"
#include "ceres/problem_impl.h"
#include "ceres/solver.cc"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1472, TC1_CallsTarget) {
  Solver::Options options{};
  ceres::PreSolveSummarize(options, nullptr, nullptr);
}
