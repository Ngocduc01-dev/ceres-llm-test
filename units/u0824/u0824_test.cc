// FILE: u0824_test.cc
#include "gtest/gtest.h"
#include "ceres/block_jacobian_writer.h"
#include "ceres/sparse_matrix.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0824, TC1_CallsTarget) {
   int{};
   int{};
  ceres::internal::BlockJacobianWriter object{};
  object.Write(int, int, nullptr, nullptr);
}
