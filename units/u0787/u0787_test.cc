// FILE: u0787_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"
#include "ceres/product_manifold.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0787, TC1_CallsTarget) {
  MatrixRef arg1{};
  internal::FixedArray<double> arg2{};
  std::index_sequence<> arg3{};
  ceres::ProductManifold object{};
  object.PlusJacobianImpl(nullptr, arg1, arg2, arg3);
}
