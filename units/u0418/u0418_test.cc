// FILE: u0418_test.cc
#include "gtest/gtest.h"
#include "ceres/subset_preconditioner.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0418, PathP1) {
  ceres::internal::SubsetPreconditioner target;
  target.num_rows();
}
