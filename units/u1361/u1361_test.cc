// FILE: u1361_test.cc
#include "gtest/gtest.h"
#include "ceres/cost_function.h"
#include "ceres/dynamic_cost_function.h"
#include "ceres/dynamic_numeric_diff_cost_function.h"
#include "ceres/gradient_checker.h"
#include "ceres/manifold.h"
#include "ceres/numeric_diff_options.h"

// P1: START -> 1 -> END
TEST(u1361_Test, TC1_CallsTarget) {
  ceres::GradientChecker target{};
}

// P2: START -> 1 -> END
TEST(u1361_Test, TC2_CallsTarget) {
  ceres::GradientChecker target{};
}

// P3: START -> 1 -> END
TEST(u1361_Test, TC3_CallsTarget) {
  ceres::GradientChecker target{};
}
