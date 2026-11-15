// FILE: u0721_test.cc
#include "gtest/gtest.h"
#include "ceres/dense_cholesky.h"
#include "ceres/iterative_refiner.h"

// Path P1 calls Solve(const double * rhs, double * solution, std::string * message).
TEST(Unitu0721, CallsTarget) {
  double rhs_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double solution_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double message_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.Solve(rhs_data, solution_data, message_data);
}
