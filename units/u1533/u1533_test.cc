// FILE: u1533_test.cc
#include "gtest/gtest.h"
#include "ceres/problem.h"
#include "ceres/solver.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/gradient_checking_cost_function.h"
#include "ceres/preprocessor.h"
#include "ceres/problem_impl.h"
#include "ceres/program.h"

// P1: START -> 1 -> END
TEST(u1533_Test, TC1_CallsTarget) {
  ceres::Solver target{};
  target.Solve(nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1533_Test, TC2_CallsTarget) {
  ceres::Solver target{};
  target.Solve(nullptr, nullptr, nullptr);
}

// P3: START -> 1 -> END
TEST(u1533_Test, TC3_CallsTarget) {
  ceres::Solver target{};
  target.Solve(nullptr, nullptr, nullptr);
}

// P4: START -> 1 -> END
TEST(u1533_Test, TC4_CallsTarget) {
  ceres::Solver target{};
  target.Solve(nullptr, nullptr, nullptr);
}
