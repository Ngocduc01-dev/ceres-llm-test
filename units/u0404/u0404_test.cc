// FILE: u0404_test.cc
#include "gtest/gtest.h"
#include "ceres/schur_complement_solver.h"

namespace ceres {
namespace internal {

// P1: START -> END (không có điểm rẽ nhánh)
TEST(DenseSchurComplementSolverDestructorTest, TC1_DestroyObject) {
  LinearSolver::Options options;
  {
    DenseSchurComplementSolver solver(options);
  }  // destructor được gọi tại đây khi ra khỏi scope
  SUCCEED();
}

}  // namespace internal
}  // namespace ceres
