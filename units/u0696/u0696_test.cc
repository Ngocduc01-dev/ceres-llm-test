// FILE: u0696_test.cc
#include "gtest/gtest.h"
#include "ceres/numeric_diff_cost_function.h"
#include "ceres/numeric_diff_options.h"
#include "ceres/sized_cost_function.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0696, CallsTarget) {
  double functor_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.NumericDiffCostFunction(functor_data, {}, 1, {});
}
