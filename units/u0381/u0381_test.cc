// FILE: u0381_test.cc
#include "gtest/gtest.h"
#include "ceres/preconditioner.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0381, PathP1) {
  ceres::internal::Preconditioner::Options target();
  target.Options();
}
