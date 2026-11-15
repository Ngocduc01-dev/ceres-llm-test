// FILE: u0593_test.cc
#include "gtest/gtest.h"
#include "ceres/tiny_solver.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0593, CallsTarget) {
  double arg0_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.Initialize(arg0_data);
}
