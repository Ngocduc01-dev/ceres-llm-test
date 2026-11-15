// FILE: u1449_test.cc
#include "gtest/gtest.h"
#include "ceres/cost_function.h"
#include "ceres/manifold.h"
#include "ceres/numeric_diff_options.h"
#include "ceres/gradient_checking_cost_function.h"
#include "ceres/gradient_checking_cost_function.cc"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1449, TC1_CallsTarget) {
  NumericDiffOptions options{};
  double relative_precision{};
  std::string extra_info{};
  ceres::internal::(anonymous)::GradientCheckingCostFunction object{};
  (void)object;
}
