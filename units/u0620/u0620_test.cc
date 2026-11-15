// FILE: u0620_test.cc
#include "gtest/gtest.h"
#include "ceres/dynamic_autodiff_cost_function.h"

// Path P1 calls DynamicAutoDiffCostFunction(CostFunctor * functor, Ownership ownership).
TEST(Unitu0620, CallsTarget) {
  double functor_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.DynamicAutoDiffCostFunction(functor_data, {});
}
