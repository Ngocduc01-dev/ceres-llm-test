// FILE: u0281_test.cc
#include "gtest/gtest.h"
#include "ceres/dogleg_strategy.h"

TEST(Unit_u0281, PathP1) {
  ceres::internal::TrustRegionStrategy::Options options;
  ceres::internal::LinearSolver::Options solver_options;
  auto linear_solver = ceres::internal::LinearSolver::Create(solver_options);
  options.linear_solver = linear_solver.get();
  ceres::internal::DoglegStrategy target(options);
  target.StepRejected(0.5);
  EXPECT_DOUBLE_EQ(target.Radius(), options.initial_radius * 0.5);
}
