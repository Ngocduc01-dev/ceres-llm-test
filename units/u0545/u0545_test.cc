// FILE: u0545_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/memory.h"
#include <memory>

// Path P1: START -> 1 -> 2 -> 3 -> 4 -> 5 -> 2 -> END.
TEST(Unit_u0545, PathP1) {
  std::allocator<int> alloc;
  int destination[1] = {};
  const int source[1] = {1};
  ceres::internal::CopyRange(alloc, destination, source, source + 1);
}
