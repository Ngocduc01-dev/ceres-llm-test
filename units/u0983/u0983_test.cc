// FILE: u0983_test.cc
#include "gtest/gtest.h"
#include "ceres/sphere_manifold.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0983, TC1_CallsTarget) {
  ceres::SphereManifold object{};
  object.TangentSize();
}
