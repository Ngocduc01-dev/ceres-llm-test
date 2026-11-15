// FILE: u0692_test.cc
#include "gtest/gtest.h"
#include "ceres/linear_operator.h"
#include "ceres/preconditioner.h"

// Path P1 calls Update(const LinearOperator & A, const double * D).
TEST(Unitu0692, CallsTarget) {
  double D_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.Update({}, D_data);
}
