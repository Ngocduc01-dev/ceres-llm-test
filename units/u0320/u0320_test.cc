// FILE: u0320_test.cc
#include "gtest/gtest.h"
#include "ceres/iterative_schur_complement_solver.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0320, PathP1) {
  { ceres::internal::IterativeSchurComplementSolver target; }
}
