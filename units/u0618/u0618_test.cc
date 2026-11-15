// FILE: u0618_test.cc
#include "gtest/gtest.h"
#include "ceres/autodiff_manifold.h"

// Path P1 calls PlusWrapper(const Functor & functor).
TEST(Unitu0618, CallsTarget) {
  object.PlusWrapper({});
}
