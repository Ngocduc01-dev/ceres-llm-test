// FILE: u1449_test.cc
#include "gtest/gtest.h"
#include "ceres/cost_function.h"
#include "ceres/manifold.h"
#include "ceres/numeric_diff_options.h"
#include "ceres/gradient_checking_cost_function.h"
#include "ceres/gradient_checking_cost_function.cc"

// P1: START -> 1 -> END
TEST(u1449_Test, TC1_CallsTarget) {
  ceres::internal::(anonymous)::GradientCheckingCostFunction target{};
}
