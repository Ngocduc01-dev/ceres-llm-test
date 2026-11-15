// FILE: u0508_test.cc
#include "gtest/gtest.h"
#include "ceres/loss_function.h"

// Path P1 calls ~ComposedLoss().
TEST(Unitu0508, CallsTarget) {
  ComposedLoss object(f_data, {}, g_data, {});
}

// Path P2 calls ~ComposedLoss() on the alternate CFG path.
TEST(Unitu0508, CallsTargetAlternate) {
  ComposedLoss object(f_data, {}, g_data, {});
}
