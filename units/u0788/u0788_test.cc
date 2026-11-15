// FILE: u0788_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"
#include "ceres/product_manifold.h"

// P1: START -> 1 -> END
TEST(MinusJacobianImplTest, TC1_CallsTarget) {
  ProductManifold object{};
  double a0[5] = {};
  MatrixRef & a1{};
  double a2 = 0.0;
  std::index_sequence<> a3{};
  object.MinusJacobianImpl(a0, a1, a2, a3);
}

