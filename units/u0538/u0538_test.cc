// FILE: u0538_test.cc
#include "gtest/gtest.h"
#include "ceres/corrector.h"

// Path P1 calls Corrector(const double sq_norm, const double[3] rho).
TEST(Unitu0538, CallsTarget) {
  double rho_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.Corrector(1.0, rho_data);
}
