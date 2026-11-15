// FILE: u0320_test.cc
#include "gtest/gtest.h"
#include "ceres/iterative_schur_complement_solver.h"

namespace ceres {
namespace internal {

// Path P1: START -> END (không có điểm rẽ nhánh)
TEST(IterativeSchurComplementSolverDestructorTest, TC1_ConstructThenDestroy) {
  LinearSolver::Options options;
  {
    IterativeSchurComplementSolver solver(options);
  }  // destructor được gọi tại đây
  SUCCEED();
}

}  // namespace internal
}  // namespace ceres
