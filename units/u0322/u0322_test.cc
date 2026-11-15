// FILE: u0322_test.cc
#include "gtest/gtest.h"
#include "ceres/levenberg_marquardt_strategy.h"

TEST(Unit_u0322, PathP1) {
  ceres::internal::TrustRegionStrategy::Options options;
  ceres::internal::LinearSolver::Options solver_options;
  auto linear_solver = ceres::internal::LinearSolver::Create(solver_options);
  options.linear_solver = linear_solver.get();
  ceres::internal::LevenbergMarquardtStrategy target(options);
  target.StepRejected(1.0);
}
