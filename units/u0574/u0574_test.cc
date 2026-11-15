// FILE: u0574_test.cc
#include "gtest/gtest.h"
#include "ceres/block_random_access_sparse_matrix.h"

#include <cstdint>

// Path P1 calls IntPairToInt64(int row, int col) const.
TEST(Unitu0574, CallsTarget) {
  object.IntPairToInt64(1, 1);
}
