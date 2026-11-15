// FILE: u0568_test.cc
#include "gtest/gtest.h"
#include "ceres/product_manifold.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0568, CallsTarget) {
  double arg0_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double arg1_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double arg2_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.MinusImpl(arg0_data, arg1_data, arg2_data, {});
}
