// FILE: u0407_test.cc
#include "gtest/gtest.h"
#include "ceres/schur_eliminator.h"
#include "ceres/schur_eliminator_impl.h"
#include "ceres/stl_util.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0407, PathP1) {
  { ceres::SchurEliminator<> target; }
}
