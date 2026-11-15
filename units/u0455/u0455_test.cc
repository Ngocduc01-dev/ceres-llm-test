// FILE: u0455_test.cc
#include "gtest/gtest.h"
#include "ceres/numeric_diff_cost_function.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0455, PathP1) {
  { ceres::NumericDiffCostFunction<EasyFunctor, CENTRAL, 3, 5, 5> target; }
}

// Path P2: START -> 1 -> END.
TEST(Unit_u0455, PathP2) {
  { ceres::NumericDiffCostFunction<EasyFunctor, CENTRAL, 3, 5, 5> target; }
}
