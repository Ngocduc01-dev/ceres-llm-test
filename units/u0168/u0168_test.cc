// FILE: u0168_test.cc
#include "gtest/gtest.h"
#include "ceres/line_manifold.h"

namespace ceres {

// TC1 - P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(LineManifoldConstructorTest, DefaultConstructorFixedSize3) {
  LineManifold<3> manifold;
  (void)manifold;
}

}  // namespace ceres
