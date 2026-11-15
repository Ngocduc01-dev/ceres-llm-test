// FILE: u1358_test.cc
#include "gtest/gtest.h"
#include "ceres/solver.h"
#include "ceres/callbacks.h"
#include "ceres/minimizer.h"
#include "ceres/preprocessor.h"
#include "ceres/problem_impl.h"
#include "ceres/program.h"

// P1: START -> 1 -> END
TEST(u1358_Test, TC1_CallsTarget) {
  SetupCommonMinimizerOptions(nullptr);
}

// P2: START -> 1 -> END
TEST(u1358_Test, TC2_CallsTarget) {
  SetupCommonMinimizerOptions(nullptr);
}

// P3: START -> 1 -> END
TEST(u1358_Test, TC3_CallsTarget) {
  SetupCommonMinimizerOptions(nullptr);
}
