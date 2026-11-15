// FILE: u0178_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(EuclideanManifoldAmbientSizeTest, P1_ReturnSize) {
  ceres::EuclideanManifold<ceres::DYNAMIC> manifold(3);
  manifold.AmbientSize();
}
