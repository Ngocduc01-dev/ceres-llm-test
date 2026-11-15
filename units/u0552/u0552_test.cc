// FILE: u0552_test.cc
#include "gtest/gtest.h"
#include "ceres/corrector.h"

// Path P1 calls CorrectJacobian(const int num_rows, const int num_cols, double * residuals, double * jacobian).
TEST(Unitu0552, CallsTarget) {
  double residuals_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double jacobian_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.CorrectJacobian(1, 1, residuals_data, jacobian_data);
}
