// FILE: u0313_test.cc
#include "gtest/gtest.h"
#include "ceres/implicit_schur_complement.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0313, PathP1) {
  ceres::internal::ImplicitSchurComplement target;
  target.num_cols();
}
