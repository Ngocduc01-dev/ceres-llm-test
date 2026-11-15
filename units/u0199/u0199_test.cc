// FILE: u0199_test.cc
#include "gtest/gtest.h"
#include "ceres/product_manifold.h"

#include <vector>

namespace ceres {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(ProductManifoldAmbientSizeTest, P1_ReturnAmbientSize) {
  std::vector<int> constant_parameters = {1};
  SubsetManifold subset_a(3, constant_parameters);
  SubsetManifold subset_b(3, constant_parameters);
  ProductManifold<SubsetManifold, SubsetManifold> manifold(subset_a, subset_b);
  manifold.AmbientSize();
}

}  // namespace ceres
