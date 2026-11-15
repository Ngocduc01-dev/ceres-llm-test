// FILE: u0291_test.cc
#include "gtest/gtest.h"
#include "ceres/eigensparse.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0291, PathP1) {
  
  ceres::internal::EigenSparse::IsNestedDissectionAvailable();
}
