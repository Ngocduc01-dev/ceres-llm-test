// FILE: u0389_test.cc
#include "gtest/gtest.h"
#include "ceres/problem_impl.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(ProblemImplHasParameterBlockTest, P1_SingleStatementPath) {
  ProblemImpl problem;
  double x[3] = {1.0, 2.0, 3.0};
  problem.HasParameterBlock(x);
}

}  // namespace internal
}  // namespace ceres
