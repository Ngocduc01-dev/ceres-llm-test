// FILE: u1355_test.cc
#include "gtest/gtest.h"
#include "ceres/evaluator.h"
#include "ceres/execution_summary.h"
#include "ceres/gradient_problem_evaluator.h"
#include "ceres/sparse_matrix.h"

// P1: START -> 1 -> END
TEST(u1355_Test, TC1_CallsTarget) {
  ceres::internal::GradientProblemEvaluator target{};
  target.Evaluate(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1355_Test, TC2_CallsTarget) {
  ceres::internal::GradientProblemEvaluator target{};
  target.Evaluate(nullptr, nullptr, nullptr, nullptr, nullptr, nullptr);
}
