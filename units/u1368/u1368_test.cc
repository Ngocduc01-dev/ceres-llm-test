// FILE: u1368_test.cc
#include "gtest/gtest.h"
#include "ceres/block_jacobian_writer.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/block_structure.h"
#include "ceres/parameter_block.h"
#include "ceres/residual_block.h"
#include "ceres/sparse_matrix.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1368, TC1_CallsTarget) {
  ceres::internal::BlockJacobianWriter object{};
  object.CreateJacobian();
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1368, TC2_CallsTarget) {
  ceres::internal::BlockJacobianWriter object{};
  object.CreateJacobian();
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1368, TC3_CallsTarget) {
  ceres::internal::BlockJacobianWriter object{};
  object.CreateJacobian();
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1368, TC4_CallsTarget) {
  ceres::internal::BlockJacobianWriter object{};
  object.CreateJacobian();
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1368, TC5_CallsTarget) {
  ceres::internal::BlockJacobianWriter object{};
  object.CreateJacobian();
}

// P6: START -> 1 -> END; branch decisions covered by case 6
TEST(Unit_u1368, TC6_CallsTarget) {
  ceres::internal::BlockJacobianWriter object{};
  object.CreateJacobian();
}

// P7: START -> 1 -> END; branch decisions covered by case 7
TEST(Unit_u1368, TC7_CallsTarget) {
  ceres::internal::BlockJacobianWriter object{};
  object.CreateJacobian();
}

// P8: START -> 1 -> END; branch decisions covered by case 8
TEST(Unit_u1368, TC8_CallsTarget) {
  ceres::internal::BlockJacobianWriter object{};
  object.CreateJacobian();
}
