// FILE: u0747_test.cc
#include "gtest/gtest.h"
#include "ceres/eigensparse.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0747, CallsTarget) {
  double rhs_ptr_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double solution_ptr_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double message_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.Solve(rhs_ptr_data, solution_ptr_data, message_data);
}
