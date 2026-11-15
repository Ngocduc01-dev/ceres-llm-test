// FILE: u1068_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"
#include "ceres/product_manifold.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1068, TC1_CallsTarget) {
  ceres::ProductManifold object{};
  object.PlusJacobian(nullptr, nullptr);
}
