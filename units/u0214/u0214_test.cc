// FILE: u0214_test.cc
#include "gtest/gtest.h"
#include "ceres/sphere_manifold.h"

namespace ceres {
namespace internal {

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(SphereManifoldConstructorTest, DefaultConstructorStaticSize4) {
  SphereManifold<4> manifold;
  (void)manifold;
}

}  // namespace internal
}  // namespace ceres
