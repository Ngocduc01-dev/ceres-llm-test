// FILE: u0509_test.cc
#include "gtest/gtest.h"
#include "ceres/schur_complement_solver.h"

// Path P1 calls ~SparseSchurComplementSolver().
TEST(Unitu0509, CallsTarget) {
  SparseSchurComplementSolver object({});
}
