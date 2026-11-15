// FILE: u0622_test.cc
#include "gtest/gtest.h"
#include "ceres/dynamic_numeric_diff_cost_function.h"
#include "ceres/numeric_diff_options.h"

struct LocalCostFunctor {};
// Path P1: START -> 1 -> END.
TEST(Unit_u0622, PathP1) {
  ceres::DynamicNumericDiffCostFunction<LocalCostFunctor, ceres::RIDDERS> target(
      nullptr, ceres::TAKE_OWNERSHIP);
}
