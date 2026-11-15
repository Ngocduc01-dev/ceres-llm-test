// FILE: u0416_test.cc
#include "gtest/gtest.h"
#include "ceres/sparse_normal_cholesky_solver.h"

namespace ceres {
namespace internal {

// P1: START -> END (không có điểm rẽ nhánh)
TEST(SparseNormalCholeskySolverDestructorTest, DestroyObject) {
  LinearSolver::Options options;
  {
    SparseNormalCholeskySolver solver(options);
  }  // destructor được gọi ở đây
  SUCCEED();
}

}  // namespace internal
}  // namespace ceres
