// FILE: u0456_test.cc
#include "gtest/gtest.h"
#include "ceres/numeric_diff_first_order_function.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0456, PathP1) {
  { ceres::NumericDiffFirstOrderFunction<QuadraticCostFunctor, CENTRAL, 4> target; }
}
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0456, PathP2) {
  { ceres::NumericDiffFirstOrderFunction<QuadraticCostFunctor, CENTRAL, 4> target; }
}
