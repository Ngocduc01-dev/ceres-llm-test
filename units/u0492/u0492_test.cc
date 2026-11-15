// FILE: u0492_test.cc
#include "gtest/gtest.h"
#include "ceres/trust_region_step_evaluator.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0492, PathP1) {
  const double arg_0 = 1.0;
  const double arg_1 = 1.0;
  ceres::internal::TrustRegionStepEvaluator target(arg_0, arg_1);
  target.StepQuality(1.0, 1.0);
}
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0492, PathP2) {
  const double arg_0 = 1.0;
  const double arg_1 = 1.0;
  ceres::internal::TrustRegionStepEvaluator target(arg_0, arg_1);
  target.StepQuality(1.0, 1.0);
}
