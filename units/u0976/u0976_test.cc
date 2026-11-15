// FILE: u0976_test.cc
#include "gtest/gtest.h"
#include "ceres/cost_function.h"
#include "ceres/dynamic_cost_function.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0976, TC1_CallsTarget) {
  int num_residuals{};
  ceres::DynamicCostFunction object{};
  object.SetNumResiduals(num_residuals);
}
