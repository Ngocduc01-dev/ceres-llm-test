// FILE: u0648_test.cc
#include "gtest/gtest.h"
#include "ceres/block_jacobi_preconditioner.h"
#include "ceres/block_random_access_diagonal_matrix.h"

// Path P1 calls matrix() const.
TEST(Unitu0648, CallsTarget) {
  object.matrix();
}
