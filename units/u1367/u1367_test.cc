// FILE: u1367_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/implicit_schur_complement.h"
#include "ceres/partitioned_matrix_view.h"

// P1: START -> 1 -> END
TEST(u1367_Test, TC1_CallsTarget) {
  ceres::internal::ImplicitSchurComplement target{};
  target.Init(nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1367_Test, TC2_CallsTarget) {
  ceres::internal::ImplicitSchurComplement target{};
  target.Init(nullptr, nullptr, nullptr);
}

// P3: START -> 1 -> END
TEST(u1367_Test, TC3_CallsTarget) {
  ceres::internal::ImplicitSchurComplement target{};
  target.Init(nullptr, nullptr, nullptr);
}

// P4: START -> 1 -> END
TEST(u1367_Test, TC4_CallsTarget) {
  ceres::internal::ImplicitSchurComplement target{};
  target.Init(nullptr, nullptr, nullptr);
}
