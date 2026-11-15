// FILE: u0704_test.cc
#include "gtest/gtest.h"
#include "ceres/dense_cholesky.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0704, CallsTarget) {
  double lhs_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double rhs_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double solution_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double message_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.FactorAndSolve(1, lhs_data, rhs_data, solution_data, message_data);
}
