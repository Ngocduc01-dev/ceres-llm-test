// FILE: u0462_test.cc
#include "gtest/gtest.h"
#include "ceres/sphere_manifold.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0462, PathP1) {
  ceres::SphereManifold<4> target;
  target.AmbientSize();
}
