// FILE: u0198_test.cc
#include "gtest/gtest.h"
#include "ceres/product_manifold.h"

namespace ceres {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(ProductManifoldConstructorTest, TC1_EuclideanAndSphere) {
  ProductManifold<EuclideanManifold<3>, SphereManifold<4>> manifold(
      EuclideanManifold<3>(), SphereManifold<4>());
  (void)manifold;
}

}  // namespace ceres
