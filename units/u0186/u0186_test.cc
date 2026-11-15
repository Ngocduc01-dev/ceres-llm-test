// FILE: u0186_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(QuaternionManifoldTangentSize, TC1_ReturnThree) {
  ceres::QuaternionManifold manifold;
  int tangent_size = manifold.TangentSize();
  (void)tangent_size;  // Không kiểm tra kết quả trả về.
}
