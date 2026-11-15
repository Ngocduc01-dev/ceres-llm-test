// FILE: u0566_test.cc
#include "gtest/gtest.h"
#include "ceres/product_manifold.h"
#include <utility>

// Path P1: START -> 1 -> END.
TEST(Unit_u0566, PathP1) {
  ceres::SubsetManifold first(2, {1});
  ceres::SubsetManifold second(2, {0});
  ceres::ProductManifold<ceres::SubsetManifold, ceres::SubsetManifold> target(
      std::index_sequence<0, 1>{}, first, second);
}
