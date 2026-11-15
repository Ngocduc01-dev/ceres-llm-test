// FILE: u0407_test.cc
#include "gtest/gtest.h"
#include "ceres/schur_eliminator.h"
// Path P1: START -> 1 -> END.
TEST(Unit_u0407, PathP1) { ceres::LinearSolver::Options options; ceres::internal::SchurEliminator<> target(options); }
