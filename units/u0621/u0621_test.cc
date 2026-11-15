// FILE: u0621_test.cc
#include "gtest/gtest.h"
#include "ceres/dynamic_autodiff_cost_function.h"

// Path P1 calls DynamicAutoDiffCostFunction(DynamicAutoDiffCostFunction<CostFunctor, Stride> && other).
TEST(Unitu0621, CallsTarget) {
  object.DynamicAutoDiffCostFunction({});
}
