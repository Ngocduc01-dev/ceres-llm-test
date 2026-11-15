// FILE: u1201_test.cc
#include "gtest/gtest.h"
#include "ceres/fake_bundle_adjustment_jacobian.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/block_structure.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1201, TC1_CallsTarget) {
  int num_cameras{};
  int num_points{};
  int camera_size{};
  int point_size{};
  double visibility{};
  std::mt19937 prng{};
  ceres::internal::CreateFakeBundleAdjustmentJacobian(num_cameras, num_points, camera_size, point_size, visibility, prng);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1201, TC2_CallsTarget) {
  int num_cameras{};
  int num_points{};
  int camera_size{};
  int point_size{};
  double visibility{};
  std::mt19937 prng{};
  ceres::internal::CreateFakeBundleAdjustmentJacobian(num_cameras, num_points, camera_size, point_size, visibility, prng);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1201, TC3_CallsTarget) {
  int num_cameras{};
  int num_points{};
  int camera_size{};
  int point_size{};
  double visibility{};
  std::mt19937 prng{};
  ceres::internal::CreateFakeBundleAdjustmentJacobian(num_cameras, num_points, camera_size, point_size, visibility, prng);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1201, TC4_CallsTarget) {
  int num_cameras{};
  int num_points{};
  int camera_size{};
  int point_size{};
  double visibility{};
  std::mt19937 prng{};
  ceres::internal::CreateFakeBundleAdjustmentJacobian(num_cameras, num_points, camera_size, point_size, visibility, prng);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1201, TC5_CallsTarget) {
  int num_cameras{};
  int num_points{};
  int camera_size{};
  int point_size{};
  double visibility{};
  std::mt19937 prng{};
  ceres::internal::CreateFakeBundleAdjustmentJacobian(num_cameras, num_points, camera_size, point_size, visibility, prng);
}

// P6: START -> 1 -> END; branch decisions covered by case 6
TEST(Unit_u1201, TC6_CallsTarget) {
  int num_cameras{};
  int num_points{};
  int camera_size{};
  int point_size{};
  double visibility{};
  std::mt19937 prng{};
  ceres::internal::CreateFakeBundleAdjustmentJacobian(num_cameras, num_points, camera_size, point_size, visibility, prng);
}
