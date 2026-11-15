// FILE: u0703_test.cc
#include "gtest/gtest.h"
#include "ceres/iteration_callback.h"
#include "ceres/callbacks.h"

// Path P1 calls operator()(const IterationSummary & summary).
TEST(Unitu0703, CallsTarget) {
  object.operator({});
}
