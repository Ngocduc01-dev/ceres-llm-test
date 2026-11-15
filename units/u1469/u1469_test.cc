// FILE: u1469_test.cc
#include "gtest/gtest.h"
#include "ceres/covariance_impl.h"
#include "ceres/map_util.h"
#include "ceres/parallel_for.h"
#include "ceres/parameter_block.h"
#include "ceres/problem_impl.h"

// P1: START -> 1 -> END
TEST(u1469_Test, TC1_CallsTarget) {
  ceres::internal::CovarianceImpl target{};
  target.GetCovarianceMatrixInTangentOrAmbientSpace(nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1469_Test, TC2_CallsTarget) {
  ceres::internal::CovarianceImpl target{};
  target.GetCovarianceMatrixInTangentOrAmbientSpace(nullptr, nullptr, nullptr);
}

// P3: START -> 1 -> END
TEST(u1469_Test, TC3_CallsTarget) {
  ceres::internal::CovarianceImpl target{};
  target.GetCovarianceMatrixInTangentOrAmbientSpace(nullptr, nullptr, nullptr);
}
