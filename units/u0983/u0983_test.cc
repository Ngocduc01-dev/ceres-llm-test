// FILE: u0983_test.cc
#include "gtest/gtest.h"
#include "ceres/sphere_manifold.h"

// P1: START -> 1 -> END
TEST(TangentSizeTest, TC1_CallsTarget) {
  SphereManifold object{};
  object.TangentSize();
}

