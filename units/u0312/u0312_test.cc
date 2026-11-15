// FILE: u0312_test.cc
#include "gtest/gtest.h"
#include "ceres/implicit_schur_complement.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0312, PathP1) {
  ceres::internal::ImplicitSchurComplement target;
  target.num_rows();
}
