// FILE: u0587_test.cc
#include "gtest/gtest.h"
#include "ceres/product_manifold.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0587, CallsTarget) {
  double y_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double x_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double y_minus_x_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.MinusImpl(y_data, x_data, y_minus_x_data, {});
}
