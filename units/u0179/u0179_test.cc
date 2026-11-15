// FILE: u0179_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"

namespace ceres {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(EuclideanManifoldTangentSize, P1_ReturnSize) {
  EuclideanManifold<DYNAMIC> manifold(3);
  manifold.TangentSize();
}

}  // namespace ceres
