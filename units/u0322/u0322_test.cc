// FILE: u0322_test.cc
#include "gtest/gtest.h"
#include "ceres/levenberg_marquardt_strategy.h"

namespace ceres {
namespace internal {

namespace {

// Linear solver giả chỉ để thoả CHECK(linear_solver != nullptr) trong constructor.
// Hàm StepRejected không dùng tới solver này.
class FakeLinearSolver : public LinearSolver {
 public:
  Summary Solve(LinearOperator* /*A*/,
                const double* /*b*/,
                const PerSolveOptions& /*per_solve_options*/,
                double* /*x*/) override {
    return Summary();
  }
};

}  // namespace

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(LevenbergMarquardtStrategyStepRejectedTest, TC1_P1_StraightLine) {
  FakeLinearSolver linear_solver;

  TrustRegionStrategy::Options options;
  options.linear_solver = &linear_solver;
  options.initial_radius = 100.0;
  options.max_radius = 1e16;
  options.min_lm_diagonal = 1e-6;
  options.max_lm_diagonal = 1e32;

  LevenbergMarquardtStrategy strategy(options);
  strategy.StepRejected(0.37);
}

}  // namespace internal
}  // namespace ceres
