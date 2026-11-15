// FILE: u0788_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"
#include "ceres/product_manifold.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0788, TC1_CallsTarget) {
  MatrixRef arg1{};
  internal::FixedArray<double> arg2{};
  std::index_sequence<> arg3{};
  ceres::ProductManifold object{};
  object.MinusJacobianImpl(nullptr, arg1, arg2, arg3);
}
