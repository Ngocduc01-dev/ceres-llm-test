// FILE: u0331_test.cc
#include "gtest/gtest.h"
#include "ceres/execution_summary.h"
#include "ceres/linear_solver.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0331, PathP1) {
  ceres::internal::LinearSolver target;
  target.Statistics();
}
