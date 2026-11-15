// FILE: u0623_test.cc
#include "gtest/gtest.h"
#include "ceres/dynamic_numeric_diff_cost_function.h"

// Path P1 calls DynamicNumericDiffCostFunction(DynamicNumericDiffCostFunction<CostFunctor, kMethod> && other).
TEST(Unitu0623, CallsTarget) {
  object.DynamicNumericDiffCostFunction({});
}
