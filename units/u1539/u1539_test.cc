// FILE: u1539_test.cc
#include "gtest/gtest.h"
#include "ceres/problem.h"
#include "ceres/solver.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1539, TC1_CallsTarget) {
  ceres_solve(nullptr);
}
