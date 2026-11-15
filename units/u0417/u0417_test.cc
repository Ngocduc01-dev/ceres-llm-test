// FILE: u0417_test.cc
#include "gtest/gtest.h"
#include "ceres/subset_preconditioner.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0417, PathP1) {
  { ceres::internal::SubsetPreconditioner target; }
}
