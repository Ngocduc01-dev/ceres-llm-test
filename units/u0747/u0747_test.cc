// FILE: u0747_test.cc
#include "gtest/gtest.h"
#include "ceres/eigensparse.h"

// Path P1 calls Solve(const double * rhs_ptr, double * solution_ptr, std::string * message).
TEST(Unitu0747, CallsTarget) {
  double rhs_ptr_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double solution_ptr_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double message_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.Solve(rhs_ptr_data, solution_ptr_data, message_data);
}
