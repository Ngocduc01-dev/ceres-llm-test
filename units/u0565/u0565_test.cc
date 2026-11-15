// FILE: u0565_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/parameter_dims.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0565, CallsTarget) {
  double ptr_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.GetUnpackedParameters(ptr_data, 1);
}
