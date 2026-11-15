// FILE: u0485_test.cc
#include "gtest/gtest.h"
#include "ceres/problem_impl.h"

// P1: START -> 1 (CHECK đúng) -> END
// Path P1: START -> CFG nodes -> END.
TEST(ProblemImplResidualBlockSet, FastRemovalEnabled) {
  ceres::Problem::Options options;
  options.enable_fast_removal = true;
  ceres::internal::ProblemImpl problem(options);
  problem.residual_block_set();
}
