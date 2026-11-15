// FILE: u0824_test.cc
#include "gtest/gtest.h"
#include "ceres/block_jacobian_writer.h"
#include "ceres/sparse_matrix.h"

// P1: START -> 1 -> END
TEST(WriteTest, TC1_CallsTarget) {
  BlockJacobianWriter object{};
  i a0{};
  i a1{};
  double a2[5] = {};
  object.Write(a0, a1, a2, nullptr);
}

