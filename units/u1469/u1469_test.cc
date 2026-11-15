// FILE: u1469_test.cc
#include "gtest/gtest.h"
#include "ceres/covariance_impl.h"
#include "ceres/map_util.h"
#include "ceres/parallel_for.h"
#include "ceres/parameter_block.h"
#include "ceres/problem_impl.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1469, TC1_CallsTarget) {
  bool lift_covariance_to_ambient_space{};
  ceres::internal::CovarianceImpl object{};
  object.GetCovarianceMatrixInTangentOrAmbientSpace(nullptr, lift_covariance_to_ambient_space, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1469, TC2_CallsTarget) {
  bool lift_covariance_to_ambient_space{};
  ceres::internal::CovarianceImpl object{};
  object.GetCovarianceMatrixInTangentOrAmbientSpace(nullptr, lift_covariance_to_ambient_space, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1469, TC3_CallsTarget) {
  bool lift_covariance_to_ambient_space{};
  ceres::internal::CovarianceImpl object{};
  object.GetCovarianceMatrixInTangentOrAmbientSpace(nullptr, lift_covariance_to_ambient_space, nullptr);
}
