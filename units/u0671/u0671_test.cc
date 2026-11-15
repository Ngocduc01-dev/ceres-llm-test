// FILE: u0671_test.cc
#include "gtest/gtest.h"
#include "ceres/gradient_problem.h"
#include "ceres/gradient_problem_evaluator.h"

// Path P1 calls GradientProblemEvaluator(const GradientProblem & problem).
TEST(Unitu0671, CallsTarget) {
  object.GradientProblemEvaluator({});
}
