// FILE: u0187_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"

// P1: START -> 1 -> END
TEST(EigenQuaternionManifoldAmbientSize, TC1_ReturnsConstant) {
  ceres::EigenQuaternionManifold manifold;
  manifold.AmbientSize();
}
