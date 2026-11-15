// FILE: u0688_test.cc
#include "gtest/gtest.h"
#include "ceres/linear_operator.h"
#include "ceres/power_series_expansion_preconditioner.h"

// Path P1 calls Update(const LinearOperator &, const double *).
TEST(Unitu0688, CallsTarget) {
  double arg1_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.Update({}, arg1_data);
}
