// FILE: u0167_test.cc
#include "gtest/gtest.h"
#include "ceres/line_manifold.h"

// P1: START -> 1 -> END (hàm không có điểm rẽ nhánh)
TEST(LineManifoldTangentSizeTest, P1_StraightLineNoBranch) {
  ceres::LineManifold<3> manifold;
  int tangent_size = manifold.TangentSize();
  (void)tangent_size;  // Không kiểm tra kết quả trả về.
}
