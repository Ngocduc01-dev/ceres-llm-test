// FILE: u0668_test.cc
#include "gtest/gtest.h"
#include "ceres/dense_sparse_matrix.h"

// Path P1 calls mutable_matrix().
TEST(Unitu0668, CallsTarget) {
  object.mutable_matrix();
}
