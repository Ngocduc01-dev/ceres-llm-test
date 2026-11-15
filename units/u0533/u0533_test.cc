// FILE: u0533_test.cc
#include "gtest/gtest.h"
#include "ceres/sparse_cholesky.h"
#include "ceres/visibility_based_preconditioner.h"

// Path P1 calls RightMultiplyAndAccumulate(const double * x, double * y) const.
TEST(Unitu0533, CallsTarget) {
  double x_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double y_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.RightMultiplyAndAccumulate(x_data, y_data);
}
