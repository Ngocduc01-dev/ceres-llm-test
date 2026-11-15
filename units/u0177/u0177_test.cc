// FILE: u0177_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(EuclideanManifoldConstructor, DefaultConstructorFixedSize) {
  ceres::EuclideanManifold<3> manifold;
  (void)manifold;
}
