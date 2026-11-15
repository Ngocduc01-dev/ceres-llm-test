// FILE: u1472_test.cc
#include "gtest/gtest.h"
#include "ceres/solver.h"
#include "ceres/problem_impl.h"
#include "ceres/solver.cc"

// P1: START -> 1 -> END
TEST(u1472_Test, TC1_CallsTarget) {
  PreSolveSummarize(nullptr, nullptr, nullptr);
}
