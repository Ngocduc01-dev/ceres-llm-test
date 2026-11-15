// FILE: u0320_test.cc
#include "gtest/gtest.h"
#include "ceres/iterative_schur_complement_solver.h"

TEST(Unit_u0320, PathP1) {
  ceres::internal::LinearSolver::Options options;
  { ceres::internal::IterativeSchurComplementSolver target(options); }
}
