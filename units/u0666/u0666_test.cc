// FILE: u0666_test.cc
#include "gtest/gtest.h"
#include "ceres/dense_sparse_matrix.h"

// Path P1 calls num_nonzeros() const.
TEST(Unitu0666, CallsTarget) {
  object.num_nonzeros();
}
