// FILE: u0711_test.cc
#include "gtest/gtest.h"
#include "ceres/iteration_callback.h"
#include "ceres/gradient_checking_cost_function.h"

// Path P1 calls operator()(const IterationSummary &).
TEST(Unitu0711, CallsTarget) {
  object.operator({});
}
