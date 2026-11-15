// FILE: u1539_test.cc
#include "gtest/gtest.h"
#include "ceres/problem.h"
#include "ceres/solver.h"

// P1: START -> 1 -> END
TEST(u1539_Test, TC1_CallsTarget) {
  ceres_solve(nullptr);
}
