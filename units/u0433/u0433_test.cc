// FILE: u0433_test.cc
#include "gtest/gtest.h"
#include "ceres/trust_region_step_evaluator.h"
TEST(Unit_u0433, Constructor) { ceres::internal::TrustRegionStepEvaluator target(1.0, 1); }
