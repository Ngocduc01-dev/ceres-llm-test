// FILE: u1354_test.cc
#include "gtest/gtest.h"
#include "ceres/casts.h"
#include "ceres/dense_jacobian_writer.h"
#include "ceres/dense_sparse_matrix.h"
#include "ceres/parameter_block.h"
#include "ceres/residual_block.h"
#include "ceres/sparse_matrix.h"

// P1: START -> 1 -> END
TEST(u1354_Test, TC1_CallsTarget) {
  ceres::internal::DenseJacobianWriter target{};
  target.Write(nullptr, nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1354_Test, TC2_CallsTarget) {
  ceres::internal::DenseJacobianWriter target{};
  target.Write(nullptr, nullptr, nullptr, nullptr);
}

// P3: START -> 1 -> END
TEST(u1354_Test, TC3_CallsTarget) {
  ceres::internal::DenseJacobianWriter target{};
  target.Write(nullptr, nullptr, nullptr, nullptr);
}
