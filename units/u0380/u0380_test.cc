// FILE: u0380_test.cc
#include "gtest/gtest.h"
#include "ceres/preconditioner.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0380, PathP1) {
  { ceres::internal::Preconditioner target; }
}
