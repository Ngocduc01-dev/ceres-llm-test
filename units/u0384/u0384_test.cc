// FILE: u0384_test.cc
#include "gtest/gtest.h"
#include "ceres/preconditioner.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0384, PathP1) {
  int arg_0 = 1;
  ceres::internal::IdentityPreconditioner target(arg_0);
  target.IdentityPreconditioner(1);
}
