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

// P1: START -> 1 -> END
TEST(u1478_Test, TC1_CallsTarget) {
  PostSolveSummarize(nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1478_Test, TC2_CallsTarget) {
  PostSolveSummarize(nullptr, nullptr);
}

// P3: START -> 1 -> END
TEST(u1478_Test, TC3_CallsTarget) {
  PostSolveSummarize(nullptr, nullptr);
}

// P4: START -> 1 -> END
TEST(u1478_Test, TC4_CallsTarget) {
  PostSolveSummarize(nullptr, nullptr);
}
