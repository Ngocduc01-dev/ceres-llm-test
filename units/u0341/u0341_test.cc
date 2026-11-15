// FILE: u0341_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"

#include <vector>

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(SubsetManifoldTangentSize, P1_ReturnTangentSize) {
  const int size = 4;
  const std::vector<int> constant_parameters = {1, 3};
  ceres::SubsetManifold manifold(size, constant_parameters);
  manifold.TangentSize();
}
