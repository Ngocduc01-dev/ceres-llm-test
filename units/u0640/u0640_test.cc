// FILE: u0640_test.cc
#include "gtest/gtest.h"
#include "ceres/numeric_diff_cost_function.h"

// Path P1 calls NumericDiffCostFunction(NumericDiffCostFunction<CostFunctor, kMethod, kNumResiduals, Ns> && other).
TEST(Unitu0640, CallsTarget) {
  object.NumericDiffCostFunction({});
}
