// FILE: u1374_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/block_structure.h"
#include "ceres/inner_product_computer.h"
#include "ceres/sparse_cholesky.h"
#include "ceres/subset_preconditioner.h"

// P1: START -> 1 -> END
TEST(u1374_Test, TC1_CallsTarget) {
  ceres::internal::SubsetPreconditioner target{};
  target.UpdateImpl(nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1374_Test, TC2_CallsTarget) {
  ceres::internal::SubsetPreconditioner target{};
  target.UpdateImpl(nullptr, nullptr);
}

// P3: START -> 1 -> END
TEST(u1374_Test, TC3_CallsTarget) {
  ceres::internal::SubsetPreconditioner target{};
  target.UpdateImpl(nullptr, nullptr);
}

// P4: START -> 1 -> END
TEST(u1374_Test, TC4_CallsTarget) {
  ceres::internal::SubsetPreconditioner target{};
  target.UpdateImpl(nullptr, nullptr);
}
