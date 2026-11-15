// FILE: u0525_test.cc
#include "gtest/gtest.h"
#include "ceres/dogleg_strategy.h"

// Path P1 calls StepAccepted(double step_quality).
TEST(Unitu0525, CallsTarget) {
  object.StepAccepted(1.0);
}

// Path P2 calls StepAccepted(double step_quality) on the alternate CFG path.
TEST(Unitu0525, CallsTargetAlternate) {
  object.StepAccepted(1.0);
}
