// FILE: u0589_test.cc
#include "gtest/gtest.h"
#include "ceres/product_manifold.h"

// Path P1 calls Dereference(T* p).
TEST(Unitu0589, CallsTarget) {
  double p_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.Dereference(p_data);
}
