// FILE: u0331_test.cc
#include "gtest/gtest.h"
#include "ceres/execution_summary.h"
#include "ceres/linear_solver.h"

namespace ceres {
namespace internal {

namespace {

// Lớp con cụ thể để tạo được object (LinearSolver có hàm thuần ảo Solve).
class TestLinearSolver : public LinearSolver {
 public:
  Summary Solve(LinearOperator* A,
                const double* b,
                const PerSolveOptions& per_solve_options,
                double* x) override {
    return Summary();
  }
};

}  // namespace

// Path P1: START -> END (không có điểm rẽ nhánh)
TEST(LinearSolverStatisticsTest, P1_DefaultReturnsWithoutBranch) {
  TestLinearSolver solver;
  solver.Statistics();
}

}  // namespace internal
}  // namespace ceres
