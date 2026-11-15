// FILE: u0406_test.cc
#include "gtest/gtest.h"
#include "ceres/schur_eliminator.h"
// Path P1: START -> 1 -> END.
TEST(Unit_u0406, PathP1) { ceres::internal::SchurEliminator<1,1,1>::Chunk target(1); }
