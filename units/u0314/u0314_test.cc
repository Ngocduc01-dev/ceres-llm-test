// FILE: u0314_test.cc
#include "gtest/gtest.h"
#include "ceres/implicit_schur_complement.h"

TEST(Unit_u0314, PathP1) {
  ceres::internal::LinearSolver::Options options;
  ceres::internal::ImplicitSchurComplement target(options);
  EXPECT_TRUE(target.rhs().size() == 0);
}
