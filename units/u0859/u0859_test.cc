// FILE: u0859_test.cc
#include "gtest/gtest.h"
#include "ceres/cost_function.h"
#include "ceres/manifold.h"
#include "ceres/numeric_diff_options.h"
#include "ceres/gradient_checking_cost_function.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0859, TC1_CallsTarget) {
  double relative_step_size{};
  double relative_precision{};
  std::string extra_info{};
  ceres::internal::CreateGradientCheckingCostFunction(nullptr, nullptr, relative_step_size, relative_precision, extra_info, nullptr);
}
