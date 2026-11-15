// FILE: u0408_test.cc
#include "gtest/gtest.h"
#include "ceres/schur_jacobi_preconditioner.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0408, PathP1) {
  { ceres::internal::SchurJacobiPreconditioner target; }
}
