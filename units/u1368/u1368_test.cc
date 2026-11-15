// FILE: u1368_test.cc
#include "gtest/gtest.h"
#include "ceres/block_jacobian_writer.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/block_structure.h"
#include "ceres/parameter_block.h"
#include "ceres/residual_block.h"
#include "ceres/sparse_matrix.h"

// P1: START -> 1 -> END
TEST(u1368_Test, TC1_CallsTarget) {
  ceres::internal::BlockJacobianWriter target{};
  target.CreateJacobian();
}

// P2: START -> 1 -> END
TEST(u1368_Test, TC2_CallsTarget) {
  ceres::internal::BlockJacobianWriter target{};
  target.CreateJacobian();
}

// P3: START -> 1 -> END
TEST(u1368_Test, TC3_CallsTarget) {
  ceres::internal::BlockJacobianWriter target{};
  target.CreateJacobian();
}

// P4: START -> 1 -> END
TEST(u1368_Test, TC4_CallsTarget) {
  ceres::internal::BlockJacobianWriter target{};
  target.CreateJacobian();
}
