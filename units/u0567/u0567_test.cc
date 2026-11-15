// FILE: u0567_test.cc
#include "gtest/gtest.h"
#include "ceres/product_manifold.h"

// Path P1 calls PlusImpl(const double *, const double *, double *, std::index_sequence<>).
TEST(Unitu0567, CallsTarget) {
  double arg0_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double arg1_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double arg2_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.PlusImpl(arg0_data, arg1_data, arg2_data, {});
}
