// FILE: u0434_test.cc
#include "gtest/gtest.h"
#include "ceres/visibility_based_preconditioner.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0434, PathP1) {
  { ceres::internal::VisibilityBasedPreconditioner target; }
}
