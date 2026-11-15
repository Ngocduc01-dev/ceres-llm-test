// FILE: u0583_test.cc
#include "gtest/gtest.h"
#include "ceres/schur_complement_solver.h"

// Path P1 calls ResizeRhs(int n).
TEST(Unitu0583, CallsTarget) {
  object.ResizeRhs(1);
}
