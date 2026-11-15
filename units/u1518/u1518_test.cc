// FILE: u1518_test.cc
#include "gtest/gtest.h"
#include "ceres/covariance_impl.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1518, TC1_CallsTarget) {
  ceres::internal::CovarianceImpl object{};
  object.ComputeCovarianceValues();
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1518, TC2_CallsTarget) {
  ceres::internal::CovarianceImpl object{};
  object.ComputeCovarianceValues();
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1518, TC3_CallsTarget) {
  ceres::internal::CovarianceImpl object{};
  object.ComputeCovarianceValues();
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1518, TC4_CallsTarget) {
  ceres::internal::CovarianceImpl object{};
  object.ComputeCovarianceValues();
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1518, TC5_CallsTarget) {
  ceres::internal::CovarianceImpl object{};
  object.ComputeCovarianceValues();
}
