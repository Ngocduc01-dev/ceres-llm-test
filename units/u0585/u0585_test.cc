// FILE: u0585_test.cc
#include "gtest/gtest.h"
#include "ceres/visibility_based_preconditioner.h"

// Path P1 calls IsBlockPairOffDiagonal(const int block1, const int block2) const.
TEST(Unitu0585, CallsTarget) {
  object.IsBlockPairOffDiagonal(1, 1);
}
