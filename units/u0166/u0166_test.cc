// FILE: u0166_test.cc
#include "gtest/gtest.h"
#include "ceres/line_manifold.h"

// P1: START -> 1 -> END (không có nhánh rẽ)
TEST(LineManifoldAmbientSizeTest, TC1_SinglePath) {
  ceres::LineManifold<3> manifold;
  int ambient_size = manifold.AmbientSize();
  (void)ambient_size;  // Không kiểm tra kết quả trả về
}
