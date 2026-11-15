// FILE: u0431_test.cc
#include "gtest/gtest.h"
#include "ceres/triplet_sparse_matrix.h"

// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0431, PathP1) {
  ceres::internal::TripletSparseMatrix target;
  target.mutable_rows();
}
