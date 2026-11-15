// FILE: u1364_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"
#include "ceres/program.h"
#include "ceres/residual_block.h"
#include "ceres/triplet_sparse_matrix.h"

// P1: START -> 1 -> END
TEST(u1364_Test, TC1_CallsTarget) {
  ceres::internal::Program target{};
  target.CreateJacobianBlockSparsityTranspose(nullptr);
}

// P2: START -> 1 -> END
TEST(u1364_Test, TC2_CallsTarget) {
  ceres::internal::Program target{};
  target.CreateJacobianBlockSparsityTranspose(nullptr);
}

// P3: START -> 1 -> END
TEST(u1364_Test, TC3_CallsTarget) {
  ceres::internal::Program target{};
  target.CreateJacobianBlockSparsityTranspose(nullptr);
}

// P4: START -> 1 -> END
TEST(u1364_Test, TC4_CallsTarget) {
  ceres::internal::Program target{};
  target.CreateJacobianBlockSparsityTranspose(nullptr);
}
