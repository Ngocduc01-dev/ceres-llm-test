// FILE: u1457_test.cc
#include "gtest/gtest.h"
#include "ceres/block_structure.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/inner_product_computer.h"

// P1: START -> 1 -> END
TEST(u1457_Test, TC1_CallsTarget) {
  ceres::internal::InnerProductComputer target{};
  target.Init(nullptr);
}

// P2: START -> 1 -> END
TEST(u1457_Test, TC2_CallsTarget) {
  ceres::internal::InnerProductComputer target{};
  target.Init(nullptr);
}

// P3: START -> 1 -> END
TEST(u1457_Test, TC3_CallsTarget) {
  ceres::internal::InnerProductComputer target{};
  target.Init(nullptr);
}

// P4: START -> 1 -> END
TEST(u1457_Test, TC4_CallsTarget) {
  ceres::internal::InnerProductComputer target{};
  target.Init(nullptr);
}
