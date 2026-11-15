// FILE: u0503_test.cc
#include "gtest/gtest.h"
#include "ceres/cgnr_solver.h"

// Path P1 calls ~CgnrSolver().
TEST(Unitu0503, CallsTarget) {
  CgnrSolver object({});
}
