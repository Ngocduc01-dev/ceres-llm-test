// FILE: u0383_test.cc
#include "gtest/gtest.h"
#include "ceres/preconditioner.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0383, PathP1) {
  ceres::internal::Preconditioner target;
  target.num_cols();
}
