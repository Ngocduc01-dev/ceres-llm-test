// FILE: u1240_test.cc
#include "gtest/gtest.h"
#include "ceres/block_jacobi_preconditioner.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1240, TC1_CallsTarget) {
  ceres::internal::BlockSparseJacobiPreconditioner object{};
  object.RightMultiplyAndAccumulate(nullptr, nullptr);
}
