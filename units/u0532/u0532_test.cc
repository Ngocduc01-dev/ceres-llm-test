// FILE: u0532_test.cc
#include "gtest/gtest.h"
#include "ceres/trust_region_step_evaluator.h"

// Path P1 calls StepAccepted(const double cost, const double model_cost_change).
TEST(Unitu0532, CallsTarget) {
  object.StepAccepted(1.0, 1.0);
}

// Path P2 calls StepAccepted(const double cost, const double model_cost_change) on the alternate CFG path.
TEST(Unitu0532, CallsTargetAlternate) {
  object.StepAccepted(1.0, 1.0);
}
