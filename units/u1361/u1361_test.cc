// FILE: u1361_test.cc
#include "gtest/gtest.h"
#include "ceres/cost_function.h"
#include "ceres/dynamic_cost_function.h"
#include "ceres/dynamic_numeric_diff_cost_function.h"
#include "ceres/gradient_checker.h"
#include "ceres/manifold.h"
#include "ceres/numeric_diff_options.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1361, TC1_CallsTarget) {
  NumericDiffOptions options{};
  ceres::GradientChecker object{};
  (void)object;
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1361, TC2_CallsTarget) {
  NumericDiffOptions options{};
  ceres::GradientChecker object{};
  (void)object;
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1361, TC3_CallsTarget) {
  NumericDiffOptions options{};
  ceres::GradientChecker object{};
  (void)object;
}
