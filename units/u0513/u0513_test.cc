// FILE: u0513_test.cc
#include "gtest/gtest.h"
#include "ceres/sparse_cholesky.h"
#include "ceres/subset_preconditioner.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0513, CallsTarget) {
  double x_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double y_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.RightMultiplyAndAccumulate(x_data, y_data);
}
