// FILE: u0406_test.cc
#include "gtest/gtest.h"
#include "ceres/schur_eliminator.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0406, PathP1) {
  int arg_0 = 1;
  ceres::internal::SchurEliminator::Chunk target(arg_0);
  target.Chunk(1);
}
