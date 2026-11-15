// FILE: u0662_test.cc
#include "gtest/gtest.h"
#include "ceres/dense_sparse_matrix.h"

// Path P1 calls SetZero().
TEST(Unitu0662, CallsTarget) {
  object.SetZero();
}
