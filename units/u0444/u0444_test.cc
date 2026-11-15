// FILE: u0444_test.cc
#include "gtest/gtest.h"
#include "ceres/dynamic_numeric_diff_cost_function.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0444, PathP1) {
  { ceres::DynamicNumericDiffCostFunction<PlusFunctor, RIDDERS> target; }
}
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0444, PathP2) {
  { ceres::DynamicNumericDiffCostFunction<PlusFunctor, RIDDERS> target; }
}
