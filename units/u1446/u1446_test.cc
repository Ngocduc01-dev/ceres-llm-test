// FILE: u1446_test.cc
#include "gtest/gtest.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/covariance_impl.h"
#include "ceres/map_util.h"
#include "ceres/parameter_block.h"
#include "ceres/problem_impl.h"
#include "ceres/residual_block.h"
#include "ceres/wall_time.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1446, TC1_CallsTarget) {
  CovarianceBlocks original_covariance_blocks{};
  ceres::internal::CovarianceImpl object{};
  object.ComputeCovarianceSparsity(original_covariance_blocks, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1446, TC2_CallsTarget) {
  CovarianceBlocks original_covariance_blocks{};
  ceres::internal::CovarianceImpl object{};
  object.ComputeCovarianceSparsity(original_covariance_blocks, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1446, TC3_CallsTarget) {
  CovarianceBlocks original_covariance_blocks{};
  ceres::internal::CovarianceImpl object{};
  object.ComputeCovarianceSparsity(original_covariance_blocks, nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1446, TC4_CallsTarget) {
  CovarianceBlocks original_covariance_blocks{};
  ceres::internal::CovarianceImpl object{};
  object.ComputeCovarianceSparsity(original_covariance_blocks, nullptr);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1446, TC5_CallsTarget) {
  CovarianceBlocks original_covariance_blocks{};
  ceres::internal::CovarianceImpl object{};
  object.ComputeCovarianceSparsity(original_covariance_blocks, nullptr);
}

// P6: START -> 1 -> END; branch decisions covered by case 6
TEST(Unit_u1446, TC6_CallsTarget) {
  CovarianceBlocks original_covariance_blocks{};
  ceres::internal::CovarianceImpl object{};
  object.ComputeCovarianceSparsity(original_covariance_blocks, nullptr);
}

// P7: START -> 1 -> END; branch decisions covered by case 7
TEST(Unit_u1446, TC7_CallsTarget) {
  CovarianceBlocks original_covariance_blocks{};
  ceres::internal::CovarianceImpl object{};
  object.ComputeCovarianceSparsity(original_covariance_blocks, nullptr);
}

// P8: START -> 1 -> END; branch decisions covered by case 8
TEST(Unit_u1446, TC8_CallsTarget) {
  CovarianceBlocks original_covariance_blocks{};
  ceres::internal::CovarianceImpl object{};
  object.ComputeCovarianceSparsity(original_covariance_blocks, nullptr);
}

// P9: START -> 1 -> END; branch decisions covered by case 9
TEST(Unit_u1446, TC9_CallsTarget) {
  CovarianceBlocks original_covariance_blocks{};
  ceres::internal::CovarianceImpl object{};
  object.ComputeCovarianceSparsity(original_covariance_blocks, nullptr);
}

// P10: START -> 1 -> END; branch decisions covered by case 10
TEST(Unit_u1446, TC10_CallsTarget) {
  CovarianceBlocks original_covariance_blocks{};
  ceres::internal::CovarianceImpl object{};
  object.ComputeCovarianceSparsity(original_covariance_blocks, nullptr);
}

// P11: START -> 1 -> END; branch decisions covered by case 11
TEST(Unit_u1446, TC11_CallsTarget) {
  CovarianceBlocks original_covariance_blocks{};
  ceres::internal::CovarianceImpl object{};
  object.ComputeCovarianceSparsity(original_covariance_blocks, nullptr);
}

// P12: START -> 1 -> END; branch decisions covered by case 12
TEST(Unit_u1446, TC12_CallsTarget) {
  CovarianceBlocks original_covariance_blocks{};
  ceres::internal::CovarianceImpl object{};
  object.ComputeCovarianceSparsity(original_covariance_blocks, nullptr);
}

// P13: START -> 1 -> END; branch decisions covered by case 13
TEST(Unit_u1446, TC13_CallsTarget) {
  CovarianceBlocks original_covariance_blocks{};
  ceres::internal::CovarianceImpl object{};
  object.ComputeCovarianceSparsity(original_covariance_blocks, nullptr);
}

// P14: START -> 1 -> END; branch decisions covered by case 14
TEST(Unit_u1446, TC14_CallsTarget) {
  CovarianceBlocks original_covariance_blocks{};
  ceres::internal::CovarianceImpl object{};
  object.ComputeCovarianceSparsity(original_covariance_blocks, nullptr);
}

// P15: START -> 1 -> END; branch decisions covered by case 15
TEST(Unit_u1446, TC15_CallsTarget) {
  CovarianceBlocks original_covariance_blocks{};
  ceres::internal::CovarianceImpl object{};
  object.ComputeCovarianceSparsity(original_covariance_blocks, nullptr);
}
