// FILE: u1220_test.cc
#include "gtest/gtest.h"
#include "ceres/line_search_preprocessor.h"
#include "ceres/evaluator.h"
#include "ceres/preprocessor.h"
#include "ceres/problem_impl.h"
#include "ceres/line_search_preprocessor.cc"

// P1: START -> 1 -> END
TEST(SetupEvaluatorTest, TC1_CallsTarget) {
  SetupEvaluator(nullptr);
}

