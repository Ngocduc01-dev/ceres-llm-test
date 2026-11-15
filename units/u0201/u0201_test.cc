// FILE: u0201_test.cc
#include "gtest/gtest.h"
#include "ceres/product_manifold.h"

#include <vector>

namespace ceres {
namespace {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(ProductManifoldPlusTest, TC1_SinglePath) {
  ProductManifold<SubsetManifold,
                  SubsetManifold,
                  SubsetManifold,
                  SubsetManifold>
      manifold(SubsetManifold(1, std::vector<bool>{false}),
               SubsetManifold(1, std::vector<bool>{false}),
               SubsetManifold(1, std::vector<bool>{false}),
               SubsetManifold(1, std::vector<bool>{false}));

  const double x[4] = {0.3, -1.2, 0.7, 1.1};
  const double delta[4] = {0.5, 0.1, -0.4, 0.9};
  double x_plus_delta[4] = {0.0, 0.0, 0.0, 0.0};

  manifold.Plus(x, delta, x_plus_delta);
}

}  // namespace
}  // namespace ceres
