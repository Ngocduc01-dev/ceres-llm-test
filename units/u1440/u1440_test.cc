// FILE: u1440_test.cc
#include "gtest/gtest.h"
#include "ceres/casts.h"
#include "ceres/compressed_row_jacobian_writer.h"
#include "ceres/dynamic_compressed_row_jacobian_writer.h"
#include "ceres/dynamic_compressed_row_sparse_matrix.h"
#include "ceres/parameter_block.h"
#include "ceres/residual_block.h"
#include "ceres/sparse_matrix.h"

// P1: START -> 1 -> END
TEST(u1440_Test, TC1_CallsTarget) {
  ceres::internal::DynamicCompressedRowJacobianWriter target{};
  target.Write(nullptr, nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1440_Test, TC2_CallsTarget) {
  ceres::internal::DynamicCompressedRowJacobianWriter target{};
  target.Write(nullptr, nullptr, nullptr, nullptr);
}

// P3: START -> 1 -> END
TEST(u1440_Test, TC3_CallsTarget) {
  ceres::internal::DynamicCompressedRowJacobianWriter target{};
  target.Write(nullptr, nullptr, nullptr, nullptr);
}

// P4: START -> 1 -> END
TEST(u1440_Test, TC4_CallsTarget) {
  ceres::internal::DynamicCompressedRowJacobianWriter target{};
  target.Write(nullptr, nullptr, nullptr, nullptr);
}
