// FILE: u0550_test.cc
#include "gtest/gtest.h"
#include "ceres/low_rank_inverse_hessian.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0550, CallsTarget) {
  double x_ptr_data[5] = {1.0, 2.0, 3.0, 4.0, 5.0};
  double y_ptr_data[5] = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.RightMultiplyAndAccumulate(x_ptr_data, y_ptr_data);
}
