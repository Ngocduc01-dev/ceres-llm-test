// FILE: u1452_test.cc
#include "gtest/gtest.h"
#include "ceres/trust_region_preprocessor.h"
#include "ceres/solver.h"
#include "ceres/evaluator.h"
#include "ceres/preprocessor.h"
#include "ceres/problem_impl.h"
#include "ceres/trust_region_strategy.h"
#include "ceres/trust_region_preprocessor.cc"

// P1: START -> 1 -> END
TEST(u1452_Test, TC1_CallsTarget) {
  SetupMinimizerOptions(nullptr);
}

// P2: START -> 1 -> END
TEST(u1452_Test, TC2_CallsTarget) {
  SetupMinimizerOptions(nullptr);
}
