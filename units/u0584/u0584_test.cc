// FILE: u0584_test.cc
#include "gtest/gtest.h"
#include "ceres/schur_complement_solver.h"

// Path P1 calls rhs() const.
TEST(Unitu0584, CallsTarget) {
  object.rhs();
}
