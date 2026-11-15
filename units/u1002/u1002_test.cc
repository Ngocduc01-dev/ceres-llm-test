// FILE: u1002_test.cc
#include "gtest/gtest.h"
#include "ceres/execution_summary.h"
#include "ceres/gradient_problem_evaluator.h"

// P1: START -> 1 -> END
TEST(StatisticsTest, TC1_CallsTarget) {
  GradientProblemEvaluator object{};
  object.Statistics();
}

