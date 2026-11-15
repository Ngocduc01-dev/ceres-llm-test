// FILE: u1069_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"
#include "ceres/product_manifold.h"

// P1: START -> 1 -> END
TEST(MinusJacobianTest, TC1_CallsTarget) {
  ProductManifold object{};
  double a0[5] = {};
  double a1[5] = {};
  object.MinusJacobian(a0, a1);
}

