// FILE: u0420_test.cc
#include "gtest/gtest.h"
#include "ceres/suitesparse.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0420, PathP1) {
  ceres::internal::SuiteSparse target;
  target.IsNestedDissectionAvailable();
}
