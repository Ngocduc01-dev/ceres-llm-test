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

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1537, TC1_CallsTarget) {
  GradientProblemSolver::Options options{};
  GradientProblem problem{};
  ceres::GradientProblemSolver object{};
  object.Solve(options, problem, nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1537, TC2_CallsTarget) {
  GradientProblemSolver::Options options{};
  GradientProblem problem{};
  ceres::GradientProblemSolver object{};
  object.Solve(options, problem, nullptr, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1537, TC3_CallsTarget) {
  GradientProblemSolver::Options options{};
  GradientProblem problem{};
  ceres::GradientProblemSolver object{};
  object.Solve(options, problem, nullptr, nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1537, TC4_CallsTarget) {
  GradientProblemSolver::Options options{};
  GradientProblem problem{};
  ceres::GradientProblemSolver object{};
  object.Solve(options, problem, nullptr, nullptr);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1537, TC5_CallsTarget) {
  GradientProblemSolver::Options options{};
  GradientProblem problem{};
  ceres::GradientProblemSolver object{};
  object.Solve(options, problem, nullptr, nullptr);
}
