// FILE: u0653_test.cc
#include "gtest/gtest.h"
#include "ceres/callbacks.h"

// Path P1 calls LoggingCallback(const MinimizerType minimizer_type, const bool log_to_stdout).
TEST(Unitu0653, CallsTarget) {
  object.LoggingCallback({}, true);
}
