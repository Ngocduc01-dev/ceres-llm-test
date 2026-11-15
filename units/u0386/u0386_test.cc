// FILE: u0386_test.cc
#include "gtest/gtest.h"
#include "ceres/preconditioner.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0386, PathP1) {
  ceres::internal::IdentityPreconditioner target;
  target.num_rows();
}
