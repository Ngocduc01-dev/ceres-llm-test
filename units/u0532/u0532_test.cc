// FILE: u0532_test.cc
#include "gtest/gtest.h"
#include "ceres/trust_region_step_evaluator.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0532, CallsTarget) {
  object.StepAccepted(1.0, 1.0);
}
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0532, CallsTargetAlternate) {
  object.StepAccepted(1.0, 1.0);
}
