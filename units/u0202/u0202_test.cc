// FILE: u0202_test.cc
#include "gtest/gtest.h"
#include "ceres/product_manifold.h"

#include <vector>

namespace ceres {
namespace {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(ProductManifoldMinusTest, P1_TwoSubsetManifolds) {
  SubsetManifold m1(3, std::vector<bool>{true, false, false});  // ambient 3, tangent 2
  SubsetManifold m2(2, std::vector<bool>{false, true});         // ambient 2, tangent 1
  ProductManifold<SubsetManifold, SubsetManifold> manifold(std::move(m1),
                                                           std::move(m2));

  const double y[5] = {1.5, -2.0, 3.0, 0.5, -4.0};
  const double x[5] = {1.5, 2.5, -1.0, 0.5, 4.5};
  double y_minus_x[3] = {0.0, 0.0, 0.0};

  // Không kiểm tra kết quả trả về.
  manifold.Minus(y, x, y_minus_x);
}

}  // namespace
}  // namespace ceres
