// FILE: u1217_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/covariance_impl.h"
#include "ceres/map_util.h"
#include "ceres/parameter_block.h"
#include "ceres/problem_impl.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1217, TC1_CallsTarget) {
  bool lift_covariance_to_ambient_space{};
  ceres::internal::CovarianceImpl object{};
  object.GetCovarianceBlockInTangentOrAmbientSpace(nullptr, nullptr, lift_covariance_to_ambient_space, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1217, TC2_CallsTarget) {
  bool lift_covariance_to_ambient_space{};
  ceres::internal::CovarianceImpl object{};
  object.GetCovarianceBlockInTangentOrAmbientSpace(nullptr, nullptr, lift_covariance_to_ambient_space, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1217, TC3_CallsTarget) {
  bool lift_covariance_to_ambient_space{};
  ceres::internal::CovarianceImpl object{};
  object.GetCovarianceBlockInTangentOrAmbientSpace(nullptr, nullptr, lift_covariance_to_ambient_space, nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1217, TC4_CallsTarget) {
  bool lift_covariance_to_ambient_space{};
  ceres::internal::CovarianceImpl object{};
  object.GetCovarianceBlockInTangentOrAmbientSpace(nullptr, nullptr, lift_covariance_to_ambient_space, nullptr);
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1217, TC5_CallsTarget) {
  bool lift_covariance_to_ambient_space{};
  ceres::internal::CovarianceImpl object{};
  object.GetCovarianceBlockInTangentOrAmbientSpace(nullptr, nullptr, lift_covariance_to_ambient_space, nullptr);
}

// P6: START -> 1 -> END; branch decisions covered by case 6
TEST(Unit_u1217, TC6_CallsTarget) {
  bool lift_covariance_to_ambient_space{};
  ceres::internal::CovarianceImpl object{};
  object.GetCovarianceBlockInTangentOrAmbientSpace(nullptr, nullptr, lift_covariance_to_ambient_space, nullptr);
}

// P7: START -> 1 -> END; branch decisions covered by case 7
TEST(Unit_u1217, TC7_CallsTarget) {
  bool lift_covariance_to_ambient_space{};
  ceres::internal::CovarianceImpl object{};
  object.GetCovarianceBlockInTangentOrAmbientSpace(nullptr, nullptr, lift_covariance_to_ambient_space, nullptr);
}

// P8: START -> 1 -> END; branch decisions covered by case 8
TEST(Unit_u1217, TC8_CallsTarget) {
  bool lift_covariance_to_ambient_space{};
  ceres::internal::CovarianceImpl object{};
  object.GetCovarianceBlockInTangentOrAmbientSpace(nullptr, nullptr, lift_covariance_to_ambient_space, nullptr);
}

// P9: START -> 1 -> END; branch decisions covered by case 9
TEST(Unit_u1217, TC9_CallsTarget) {
  bool lift_covariance_to_ambient_space{};
  ceres::internal::CovarianceImpl object{};
  object.GetCovarianceBlockInTangentOrAmbientSpace(nullptr, nullptr, lift_covariance_to_ambient_space, nullptr);
}

// P10: START -> 1 -> END; branch decisions covered by case 10
TEST(Unit_u1217, TC10_CallsTarget) {
  bool lift_covariance_to_ambient_space{};
  ceres::internal::CovarianceImpl object{};
  object.GetCovarianceBlockInTangentOrAmbientSpace(nullptr, nullptr, lift_covariance_to_ambient_space, nullptr);
}

// P11: START -> 1 -> END; branch decisions covered by case 11
TEST(Unit_u1217, TC11_CallsTarget) {
  bool lift_covariance_to_ambient_space{};
  ceres::internal::CovarianceImpl object{};
  object.GetCovarianceBlockInTangentOrAmbientSpace(nullptr, nullptr, lift_covariance_to_ambient_space, nullptr);
}

// P12: START -> 1 -> END; branch decisions covered by case 12
TEST(Unit_u1217, TC12_CallsTarget) {
  bool lift_covariance_to_ambient_space{};
  ceres::internal::CovarianceImpl object{};
  object.GetCovarianceBlockInTangentOrAmbientSpace(nullptr, nullptr, lift_covariance_to_ambient_space, nullptr);
}
