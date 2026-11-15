// FILE: u0383_test.cc
#include "gtest/gtest.h"
#include "ceres/preconditioner.h"
// Path P1: START -> 1 -> END.
TEST(Unit_u0383, PathP1) { ceres::internal::IdentityPreconditioner target(1); target.num_cols(); }
