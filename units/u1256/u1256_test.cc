// FILE: u1256_test.cc
#include "gtest/gtest.h"
#include "ceres/solver.h"

// P1: START -> 1 -> END
TEST(u1256_Test, TC1_CallsTarget) {
  ceres::Solver::Summary target{};
  target.BriefReport();
}
