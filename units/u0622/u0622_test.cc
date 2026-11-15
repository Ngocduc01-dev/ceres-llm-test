// FILE: u0622_test.cc
#include "gtest/gtest.h"
#include "ceres/dynamic_numeric_diff_cost_function.h"
#include "ceres/numeric_diff_options.h"

// Path P1 calls DynamicNumericDiffCostFunction(const CostFunctor * functor, Ownership ownership, const NumericDiffOptions & options).
TEST(Unitu0622, CallsTarget) {
  double functor_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.DynamicNumericDiffCostFunction(functor_data, {}, {});
}
