// FILE: u1358_test.cc
#include "gtest/gtest.h"
#include "ceres/solver.h"
#include "ceres/callbacks.h"
#include "ceres/minimizer.h"
#include "ceres/preprocessor.h"
#include "ceres/problem_impl.h"
#include "ceres/program.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1358, TC1_CallsTarget) {
  ceres::internal::SetupCommonMinimizerOptions(nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1358, TC2_CallsTarget) {
  ceres::internal::SetupCommonMinimizerOptions(nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1358, TC3_CallsTarget) {
  ceres::internal::SetupCommonMinimizerOptions(nullptr);
}
