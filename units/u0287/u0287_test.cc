// FILE: u0287_test.cc
#include "gtest/gtest.h"
#include "ceres/dogleg_strategy.h"

namespace ceres {
namespace internal {

namespace {

// Linear solver giả, chỉ để constructor của DoglegStrategy có con trỏ
// linear_solver khác nullptr (thoả CHECK). Hàm Solve không được gọi.
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

// Path P1: START -> END (không có nhánh rẽ)
TEST(DoglegStrategySubspaceGTest, TC1_P1_ReturnsSubspaceG) {
  StubLinearSolver linear_solver;

  TrustRegionStrategy::Options options;
  options.linear_solver = &linear_solver;
  options.initial_radius = 1.0;
  options.max_radius = 10.0;
  options.min_lm_diagonal = 1e-6;
  options.max_lm_diagonal = 1e6;

  DoglegStrategy strategy(options);
  Vector g = strategy.subspace_g();
  (void)g;  // Không kiểm tra kết quả trả về
}

}  // namespace internal
}  // namespace ceres
