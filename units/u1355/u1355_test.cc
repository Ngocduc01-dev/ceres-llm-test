// FILE: u1355_test.cc
#include "gtest/gtest.h"
#include "ceres/evaluator.h"
#include "ceres/execution_summary.h"
#include "ceres/gradient_problem_evaluator.h"
#include "ceres/sparse_matrix.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1355, TC1_CallsTarget) {
  EvaluateOptions arg0{};
  ceres::internal::GradientProblemEvaluator object{};
  object.Evaluate(arg0, nullptr, nullptr, nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1355, TC2_CallsTarget) {
  EvaluateOptions arg0{};
  ceres::internal::GradientProblemEvaluator object{};
  object.Evaluate(arg0, nullptr, nullptr, nullptr, nullptr, nullptr);
}
