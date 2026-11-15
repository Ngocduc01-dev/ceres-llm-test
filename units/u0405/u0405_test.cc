// FILE: u0405_test.cc
#include "gtest/gtest.h"
#include "ceres/schur_eliminator.h"
// Path P1: START -> 1 -> END.
TEST(Unit_u0405, PathP1) { ceres::LinearSolver::Options options; ceres::internal::SchurEliminator<1,1,1> target(options); }
