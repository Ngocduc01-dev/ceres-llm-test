// FILE: u0614_test.cc
#include "gtest/gtest.h"
#include "ceres/autodiff_cost_function.h"
#include "ceres/sized_cost_function.h"

// Path P1 calls AutoDiffCostFunction(CostFunctor * functor, int num_residuals, Ownership ownership).
TEST(Unitu0614, CallsTarget) {
  double functor_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.AutoDiffCostFunction(functor_data, 1, {});
}
