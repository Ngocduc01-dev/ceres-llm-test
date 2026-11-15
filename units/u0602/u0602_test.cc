// FILE: u0602_test.cc
#include "gtest/gtest.h"
#include "ceres/trust_region_minimizer.h"
#include "ceres/trust_region_step_evaluator.h"

// Path P1 calls IsStepSuccessful().
TEST(Unitu0602, CallsTarget) {
  object.IsStepSuccessful();
}
