// FILE: u0404_test.cc
#include "gtest/gtest.h"
#include "ceres/schur_complement_solver.h"
// Path P1: START -> 1 -> END.
TEST(Unit_u0404, PathP1) { ceres::LinearSolver::Options options; ceres::internal::DenseSchurComplementSolver target(options); }
