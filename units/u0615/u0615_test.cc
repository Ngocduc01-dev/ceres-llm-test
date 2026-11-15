// FILE: u0615_test.cc
#include "gtest/gtest.h"
#include "ceres/autodiff_cost_function.h"

// Path P1 calls AutoDiffCostFunction(AutoDiffCostFunction<CostFunctor, kNumResiduals, Ns> && other).
TEST(Unitu0615, CallsTarget) {
  object.AutoDiffCostFunction({});
}
