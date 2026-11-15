// FILE: u0966_test.cc
#include "gtest/gtest.h"
#include "ceres/triplet_sparse_matrix.h"

// P1: START -> 1 -> END
TEST(AllocateMemoryTest, TC1_CallsTarget) {
  TripletSparseMatrix object{};
  object.AllocateMemory();
}

