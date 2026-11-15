// FILE: u0664_test.cc
#include "gtest/gtest.h"
#include "ceres/dense_sparse_matrix.h"

// Path P1 calls num_rows() const.
TEST(Unitu0664, CallsTarget) {
  object.num_rows();
}
