// FILE: u0692_test.cc
#include "gtest/gtest.h"
#include "ceres/linear_operator.h"
#include "ceres/preconditioner.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0692, CallsTarget) {
  double D_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.Update({}, D_data);
}
