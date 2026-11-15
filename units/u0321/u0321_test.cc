// FILE: u0321_test.cc
#include "gtest/gtest.h"
#include "ceres/levenberg_marquardt_strategy.h"

namespace ceres {
namespace internal {

// TC1 - Path P1: START -> END (destructor mặc định, không có nhánh)
TEST(LevenbergMarquardtStrategyDestructorTest, P1_StartToEnd) {
  LinearSolver::Options linear_solver_options;
  linear_solver_options.type = DENSE_QR;
  std::unique_ptr<LinearSolver> linear_solver(
      LinearSolver::Create(linear_solver_options));

  TrustRegionStrategy::Options options;
  options.linear_solver = linear_solver.get();

  std::unique_ptr<LevenbergMarquardtStrategy> strategy(
      new LevenbergMarquardtStrategy(options));
  // Gọi destructor đúng một lần.
  strategy.reset();
}

}  // namespace internal
}  // namespace ceres
