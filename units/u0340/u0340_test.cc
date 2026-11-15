// FILE: u0340_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"

#include <vector>

namespace ceres {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(SubsetManifoldAmbientSizeTest, P1_ReturnsConstancyMaskSize) {
  const int size = 4;
  const std::vector<int> constant_parameters;
  SubsetManifold manifold(size, constant_parameters);
  manifold.AmbientSize();
}

}  // namespace ceres
