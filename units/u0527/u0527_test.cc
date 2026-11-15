// FILE: u0527_test.cc
#include "gtest/gtest.h"
#include "ceres/parallel_invoke.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0527, CallsTarget) {
  object.Finished(1);
}
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0527, CallsTargetAlternate) {
  object.Finished(1);
}
