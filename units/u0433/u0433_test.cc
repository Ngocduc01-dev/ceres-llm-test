// FILE: u0433_test.cc
#include "gtest/gtest.h"
#include "ceres/trust_region_step_evaluator.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0433, PathP1) {
  const double arg_0 = 1.0;
  const int arg_1 = 1;
  ceres::internal::TrustRegionStepEvaluator target(arg_0, arg_1);
  target.TrustRegionStepEvaluator(1.0, 1);
}
