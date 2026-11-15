// FILE: u0566_test.cc
#include "gtest/gtest.h"
#include "ceres/product_manifold.h"

// Path P1 calls ProductManifold(std::index_sequence<Indices>, Args&& manifolds).
TEST(Unitu0566, CallsTarget) {
  object.ProductManifold({}, {});
}
