// FILE: u0799_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"
#include "ceres/product_manifold.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0799, TC1_CallsTarget) {
  MatrixRef jacobian{};
  internal::FixedArray<double> buffer{};
  std::index_sequence<> arg3{};
  ceres::ProductManifold object{};
  object.MinusJacobianImpl(nullptr, jacobian, buffer, arg3);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u0799, TC2_CallsTarget) {
  MatrixRef jacobian{};
  internal::FixedArray<double> buffer{};
  std::index_sequence<> arg3{};
  ceres::ProductManifold object{};
  object.MinusJacobianImpl(nullptr, jacobian, buffer, arg3);
}
