// FILE: u0313_test.cc
#include "gtest/gtest.h"
#include "ceres/implicit_schur_complement.h"

TEST(Unit_u0313, PathP1) {
  ceres::internal::LinearSolver::Options options;
  ceres::internal::ImplicitSchurComplement target(options);
  EXPECT_DEATH(target.num_cols(), "");
}
