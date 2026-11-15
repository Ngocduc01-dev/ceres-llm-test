// FILE: u0617_test.cc
#include "gtest/gtest.h"
#include "ceres/autodiff_manifold.h"

// Path P1 calls AutoDiffManifold(Functor * functor).
TEST(Unitu0617, CallsTarget) {
  double functor_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.AutoDiffManifold(functor_data);
}
