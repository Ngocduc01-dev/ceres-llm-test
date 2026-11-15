// FILE: u0314_test.cc
#include "gtest/gtest.h"
#include "ceres/implicit_schur_complement.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0314, PathP1) {
  ceres::internal::ImplicitSchurComplement target;
  target.rhs();
}
