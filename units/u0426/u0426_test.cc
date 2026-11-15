// FILE: u0426_test.cc
#include "gtest/gtest.h"
#include "ceres/triplet_sparse_matrix.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0426, PathP1) {
  ceres::internal::TripletSparseMatrix target;
  target.values();
}
