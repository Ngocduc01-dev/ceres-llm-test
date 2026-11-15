// FILE: u0613_test.cc
#include "gtest/gtest.h"
#include "ceres/autodiff_cost_function.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0613, CallsTarget) {
  double functor_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.AutoDiffCostFunction(functor_data, {});
}
