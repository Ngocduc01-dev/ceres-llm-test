// FILE: u0188_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(EigenQuaternionManifoldTangentSize, P1_ReturnsConstant) {
  ceres::EigenQuaternionManifold manifold;
  manifold.TangentSize();
}
