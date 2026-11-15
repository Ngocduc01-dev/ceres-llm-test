// FILE: u0706_test.cc
#include "gtest/gtest.h"
#include "ceres/dense_cholesky.h"

// Path P1 calls Solve(const double * rhs, double * solution, std::string * message).
TEST(Unitu0706, CallsTarget) {
  double rhs_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double solution_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double message_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.Solve(rhs_data, solution_data, message_data);
}
