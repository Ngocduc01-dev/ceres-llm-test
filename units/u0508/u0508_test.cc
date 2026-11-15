// FILE: u0508_test.cc
#include "gtest/gtest.h"
#include "ceres/loss_function.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0508, CallsTarget) {
  ComposedLoss object(f_data, {}, g_data, {});
}
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0508, CallsTargetAlternate) {
  ComposedLoss object(f_data, {}, g_data, {});
}
