// FILE: u0859_test.cc
#include "gtest/gtest.h"
#include "ceres/cost_function.h"
#include "ceres/manifold.h"
#include "ceres/numeric_diff_options.h"
#include "ceres/gradient_checking_cost_function.h"

// P1: START -> 1 -> END
TEST(CreateGradientCheckingCostFunctionTest, TC1_CallsTarget) {
  double a2 = 0.0;
  double a3 = 0.0;
  std::string & extra_info a4;
  ceres::internal::CreateGradientCheckingCostFunction(nullptr, nullptr, a2, a3, a4, nullptr);
}

