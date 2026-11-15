// FILE: u1537_test.cc
#include "gtest/gtest.h"
#include "ceres/gradient_problem.h"
#include "ceres/gradient_problem_solver.h"
#include "ceres/iteration_callback.h"
#include "ceres/solver.h"
#include "ceres/callbacks.h"
#include "ceres/evaluator.h"
#include "ceres/execution_summary.h"
#include "ceres/gradient_problem_evaluator.h"
#include "ceres/map_util.h"
#include "ceres/minimizer.h"
#include "ceres/solver_utils.h"

// P1: START -> 1 -> END
TEST(u1537_Test, TC1_CallsTarget) {
  ceres::GradientProblemSolver target{};
  target.Solve(nullptr, nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1537_Test, TC2_CallsTarget) {
  ceres::GradientProblemSolver target{};
  target.Solve(nullptr, nullptr, nullptr, nullptr);
}

// P3: START -> 1 -> END
TEST(u1537_Test, TC3_CallsTarget) {
  ceres::GradientProblemSolver target{};
  target.Solve(nullptr, nullptr, nullptr, nullptr);
}

// P4: START -> 1 -> END
TEST(u1537_Test, TC4_CallsTarget) {
  ceres::GradientProblemSolver target{};
  target.Solve(nullptr, nullptr, nullptr, nullptr);
}
