// FILE: u0612_test.cc
#include "gtest/gtest.h"
#include "ceres/dogleg_strategy.h"

// Path P1 calls ComputeTraditionalDoglegStep(double * dogleg).
TEST(Unitu0612, CallsTarget) {
  double dogleg_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.ComputeTraditionalDoglegStep(dogleg_data);
}

// Path P2 calls ComputeTraditionalDoglegStep(double * dogleg) on the alternate CFG path.
TEST(Unitu0612, CallsTargetAlternate) {
  double dogleg_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.ComputeTraditionalDoglegStep(dogleg_data);
}
