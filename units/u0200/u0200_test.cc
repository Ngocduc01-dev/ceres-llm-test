// FILE: u0200_test.cc
#include "gtest/gtest.h"
#include "ceres/product_manifold.h"

#include <vector>

namespace ceres {

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(ProductManifoldTangentSize, TC1_SinglePath) {
  ProductManifold<SubsetManifold, SubsetManifold> manifold(
      SubsetManifold(3, std::vector<bool>{true, false, false}),
      SubsetManifold(2, std::vector<bool>{false, true}));
  // Không kiểm tra giá trị trả về, chỉ gọi hàm một lần.
  manifold.TangentSize();
}

}  // namespace ceres
