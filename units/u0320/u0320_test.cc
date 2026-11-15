// FILE: u0320_test.cc
#include "gtest/gtest.h"
#include "ceres/iterative_schur_complement_solver.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0320, PathP1) {
  { ceres::internal::IterativeSchurComplementSolver target; }
}
