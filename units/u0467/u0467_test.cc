// FILE: u0467_test.cc
#include "gtest/gtest.h"
#include "ceres/levenberg_marquardt_strategy.h"

namespace ceres {
namespace internal {

// TC1 - P1: START -> 1 (CHECK_GT đúng) -> 2 -> END
// Path P1: START -> CFG nodes -> END.
TEST(LevenbergMarquardtStrategyStepAcceptedTest, P1_PositiveStepQuality) {
  LinearSolver::Options linear_solver_options;
  linear_solver_options.type = DENSE_QR;
  std::unique_ptr<LinearSolver> linear_solver(
      LinearSolver::Create(linear_solver_options));

  TrustRegionStrategy::Options options;
  options.linear_solver = linear_solver.get();
  options.initial_radius = 1e4;
  options.max_radius = 1e8;
  options.min_lm_diagonal = 1e-6;
  options.max_lm_diagonal = 1e32;

  LevenbergMarquardtStrategy strategy(options);
  strategy.StepAccepted(0.7);
}

}  // namespace internal
}  // namespace ceres
