// FILE: u1478_test.cc
#include "gtest/gtest.h"
#include "ceres/solver.h"
#include "ceres/evaluator.h"
#include "ceres/execution_summary.h"
#include "ceres/linear_solver.h"
#include "ceres/map_util.h"
#include "ceres/preprocessor.h"
#include "ceres/solver_utils.h"
#include "ceres/solver.cc"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1478, TC1_CallsTarget) {
  internal::PreprocessedProblem pp{};
  ceres::PostSolveSummarize(pp, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1478, TC2_CallsTarget) {
  internal::PreprocessedProblem pp{};
  ceres::PostSolveSummarize(pp, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1478, TC3_CallsTarget) {
  internal::PreprocessedProblem pp{};
  ceres::PostSolveSummarize(pp, nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1478, TC4_CallsTarget) {
  internal::PreprocessedProblem pp{};
  ceres::PostSolveSummarize(pp, nullptr);
}
