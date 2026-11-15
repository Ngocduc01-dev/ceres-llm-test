// FILE: u0578_test.cc
#include "gtest/gtest.h"
#include "ceres/dogleg_strategy.h"

// Path P1 calls ComputeSubspaceStepFromRoot(double y) const.
TEST(Unitu0578, CallsTarget) {
  object.ComputeSubspaceStepFromRoot(1.0);
}
