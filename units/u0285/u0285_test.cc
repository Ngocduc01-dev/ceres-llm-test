// FILE: u0285_test.cc
#include "gtest/gtest.h"
#include "ceres/dogleg_strategy.h"

namespace ceres {
namespace internal {

namespace {

// LinearSolver giả, chỉ dùng để constructor của DoglegStrategy có con trỏ hợp lệ.
class StubLinearSolver : public LinearSolver {
 public:
  Summary Solve(LinearOperator* A,
                const double* b,
                const PerSolveOptions& per_solve_options,
                double* x) override {
    return Summary();
  }
};

}  // namespace

// P1: START -> END (không có điểm rẽ nhánh)
TEST(DoglegStrategyGaussNewtonStep, P1_NoBranch) {
  StubLinearSolver solver;
  TrustRegionStrategy::Options options;
  options.linear_solver = &solver;

  DoglegStrategy strategy(options);
  Vector step = strategy.gauss_newton_step();
  (void)step;  // không kiểm tra kết quả trả về
}

}  // namespace internal
}  // namespace ceres
