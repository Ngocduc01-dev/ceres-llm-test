// FILE: u0690_test.cc
#include "gtest/gtest.h"
#include "ceres/preconditioner.h"
#include "ceres/sparse_matrix.h"

// Path P1 calls num_rows() const.
TEST(Unitu0690, CallsTarget) {
  object.num_rows();
}
