// FILE: u0650_test.cc
#include "gtest/gtest.h"
#include "ceres/block_random_access_matrix.h"

// Path P1 calls ~BlockRandomAccessMatrix().
TEST(Unitu0650, CallsTarget) {
  BlockRandomAccessMatrix object{};
}
