// FILE: u0405_test.cc
#include "gtest/gtest.h"
#include "ceres/schur_eliminator.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0405, PathP1) {
  { ceres::internal::SchurEliminatorBase target; }
}
