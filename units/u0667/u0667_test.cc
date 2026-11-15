// FILE: u0667_test.cc
#include "gtest/gtest.h"
#include "ceres/dense_sparse_matrix.h"

// Path P1 calls matrix() const.
TEST(Unitu0667, CallsTarget) {
  object.matrix();
}
