// FILE: u0288_test.cc
#include "gtest/gtest.h"
#include "ceres/dogleg_strategy.h"

TEST(Unit_u0288, PathP1) {
  ceres::internal::TrustRegionStrategy::Options options;
  ceres::internal::LinearSolver::Options solver_options;
  auto linear_solver = ceres::internal::LinearSolver::Create(solver_options);
  options.linear_solver = linear_solver.get();
  ceres::internal::DoglegStrategy target(options);
  EXPECT_EQ(target.subspace_B().rows(), 0);
}
