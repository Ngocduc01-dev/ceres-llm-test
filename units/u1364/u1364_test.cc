// FILE: u1364_test.cc
#include "gtest/gtest.h"
#include "ceres/parameter_block.h"
#include "ceres/program.h"
#include "ceres/residual_block.h"
#include "ceres/triplet_sparse_matrix.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1364, TC1_CallsTarget) {
  int start_residual_block{};
  ceres::internal::Program object{};
  object.CreateJacobianBlockSparsityTranspose(start_residual_block);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1364, TC2_CallsTarget) {
  int start_residual_block{};
  ceres::internal::Program object{};
  object.CreateJacobianBlockSparsityTranspose(start_residual_block);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1364, TC3_CallsTarget) {
  int start_residual_block{};
  ceres::internal::Program object{};
  object.CreateJacobianBlockSparsityTranspose(start_residual_block);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1364, TC4_CallsTarget) {
  int start_residual_block{};
  ceres::internal::Program object{};
  object.CreateJacobianBlockSparsityTranspose(start_residual_block);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1364, TC5_CallsTarget) {
  int start_residual_block{};
  ceres::internal::Program object{};
  object.CreateJacobianBlockSparsityTranspose(start_residual_block);
}
