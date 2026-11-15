// FILE: u0619_test.cc
#include "gtest/gtest.h"
#include "ceres/autodiff_manifold.h"

// Path P1 calls MinusWrapper(const Functor & functor).
TEST(Unitu0619, CallsTarget) {
  object.MinusWrapper({});
}
