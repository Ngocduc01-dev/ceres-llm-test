// FILE: u0603_test.cc
#include "gtest/gtest.h"
#include "ceres/visibility_based_preconditioner.h"

// Path P1 calls IsBlockPairInPreconditioner(const int block1, const int block2) const.
TEST(Unitu0603, CallsTarget) {
  object.IsBlockPairInPreconditioner(1, 1);
}
