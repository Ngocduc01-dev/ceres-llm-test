// FILE: u0659_test.cc
#include "gtest/gtest.h"
#include "ceres/dense_qr.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0659, CallsTarget) {
  double rhs_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double solution_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double message_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.Solve(rhs_data, solution_data, message_data);
}
