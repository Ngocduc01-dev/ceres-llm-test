// FILE: u0185_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(QuaternionManifoldAmbientSize, P1_ReturnsConstant) {
  ceres::QuaternionManifold manifold;
  manifold.AmbientSize();
}
