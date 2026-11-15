// FILE: u0896_test.cc
#include "gtest/gtest.h"
#include "ceres/context_impl.h"
#include "ceres/sparse_matrix.h"

// P1: START -> 1 -> END
TEST(SetZeroTest, TC1_CallsTarget) {
  SparseMatrix object{};
  i a1{};
  object.SetZero(nullptr, a1);
}

