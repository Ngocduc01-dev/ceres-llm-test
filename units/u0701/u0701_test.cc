// FILE: u0701_test.cc
#include "gtest/gtest.h"
#include "ceres/block_structure.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0701, PathP1) {
  ceres::internal::Block left(1, 0);
  ceres::internal::Block right(1, 0);
  left == right;
}
