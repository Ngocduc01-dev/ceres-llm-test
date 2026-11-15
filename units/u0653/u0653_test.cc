// FILE: u0653_test.cc
#include "gtest/gtest.h"
#include "ceres/callbacks.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0653, CallsTarget) {
  object.LoggingCallback({}, true);
}
