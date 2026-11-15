// FILE: u0538_test.cc
#include "gtest/gtest.h"
#include "ceres/corrector.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0538, CallsTarget) {
  double rho_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.Corrector(1.0, rho_data);
}
