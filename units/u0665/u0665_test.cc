// FILE: u0665_test.cc
#include "gtest/gtest.h"
#include "ceres/dense_sparse_matrix.h"

// Path P1 calls num_cols() const.
TEST(Unitu0665, CallsTarget) {
  object.num_cols();
}
