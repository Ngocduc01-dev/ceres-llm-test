// FILE: u1230_test.cc
#include "gtest/gtest.h"
#include "ceres/trust_region_preprocessor.h"
#include "ceres/ordered_groups.h"
#include "ceres/solver.h"
#include "ceres/evaluator.h"
#include "ceres/preprocessor.h"
#include "ceres/problem_impl.h"
#include "ceres/trust_region_preprocessor.cc"

// P1: START -> 1 -> END
TEST(SetupEvaluatorTest, TC1_CallsTarget) {
  SetupEvaluator(nullptr);
}

// P2: START -> 1 -> END
TEST(SetupEvaluatorTest, TC2_CallsTarget) {
  SetupEvaluator(nullptr);
}

