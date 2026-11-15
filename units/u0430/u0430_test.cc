// FILE: u0430_test.cc
#include "gtest/gtest.h"
#include "ceres/triplet_sparse_matrix.h"

// Path P1: START -> 1 -> END.
TEST(Unit_u0430, PathP1) {
  ceres::internal::TripletSparseMatrix target;
  target.cols();
}
