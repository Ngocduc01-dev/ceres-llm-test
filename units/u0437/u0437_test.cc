// FILE: u0437_test.cc
#include "gtest/gtest.h"
#include "ceres/autodiff_cost_function.h"
#include "ceres/sized_cost_function.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0437, PathP1) {
  const double *const * arg_0 = nullptr;
  double * arg_1 = nullptr;
  double ** arg_2 = nullptr;
  ceres::AutoDiffCostFunction<BinaryScalarCost, 1, 2, 2> target(arg_0, arg_1, arg_2);
  target.Evaluate(nullptr, nullptr, nullptr);
}
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0437, PathP2) {
  const double *const * arg_0 = nullptr;
  double * arg_1 = nullptr;
  double ** arg_2 = nullptr;
  ceres::AutoDiffCostFunction<BinaryScalarCost, 1, 2, 2> target(arg_0, arg_1, arg_2);
  target.Evaluate(nullptr, nullptr, nullptr);
}
