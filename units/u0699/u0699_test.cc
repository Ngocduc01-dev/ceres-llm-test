// FILE: u0699_test.cc
#include "gtest/gtest.h"
#include "ceres/block_structure.h"

// Path P1: START -> 1 -> 2 -> END.
TEST(Unit_u0699, PathP1) {
  ceres::internal::Cell left(1, 0);
  ceres::internal::Cell right(1, 1);
  ceres::internal::CellLessThan(left, right);
}
