// FILE: u0443_test.cc
#include "gtest/gtest.h"
#include "ceres/dynamic_autodiff_cost_function.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0443, PathP1) {
  { ceres::DynamicAutoDiffCostFunction<DynamicTwoParameterBlockFunctor> target; }
}

// Path P2: START -> 1 -> END.
TEST(Unit_u0443, PathP2) {
  { ceres::DynamicAutoDiffCostFunction<DynamicTwoParameterBlockFunctor> target; }
}
