// FILE: u0291_test.cc
#include "gtest/gtest.h"
#include "ceres/eigensparse.h"

TEST(Unit_u0291, PathP1) {
  // Path P1: START -> 1 -> END.
  
  ceres::internal::EigenSparse::IsNestedDissectionAvailable();
}
