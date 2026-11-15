// FILE: u1503_test.cc
#include "gtest/gtest.h"
#include "ceres/crs_matrix.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/covariance_impl.h"
#include "ceres/wall_time.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1503, TC1_CallsTarget) {
  ceres::internal::CovarianceImpl object{};
  object.ComputeCovarianceValuesUsingDenseSVD();
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1503, TC2_CallsTarget) {
  ceres::internal::CovarianceImpl object{};
  object.ComputeCovarianceValuesUsingDenseSVD();
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1503, TC3_CallsTarget) {
  ceres::internal::CovarianceImpl object{};
  object.ComputeCovarianceValuesUsingDenseSVD();
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1503, TC4_CallsTarget) {
  ceres::internal::CovarianceImpl object{};
  object.ComputeCovarianceValuesUsingDenseSVD();
}

// P5: START -> 1 -> END; branch decisions covered by case 5
TEST(Unit_u1503, TC5_CallsTarget) {
  ceres::internal::CovarianceImpl object{};
  object.ComputeCovarianceValuesUsingDenseSVD();
}

// P6: START -> 1 -> END; branch decisions covered by case 6
TEST(Unit_u1503, TC6_CallsTarget) {
  ceres::internal::CovarianceImpl object{};
  object.ComputeCovarianceValuesUsingDenseSVD();
}

// P7: START -> 1 -> END; branch decisions covered by case 7
TEST(Unit_u1503, TC7_CallsTarget) {
  ceres::internal::CovarianceImpl object{};
  object.ComputeCovarianceValuesUsingDenseSVD();
}

// P8: START -> 1 -> END; branch decisions covered by case 8
TEST(Unit_u1503, TC8_CallsTarget) {
  ceres::internal::CovarianceImpl object{};
  object.ComputeCovarianceValuesUsingDenseSVD();
}

// P9: START -> 1 -> END; branch decisions covered by case 9
TEST(Unit_u1503, TC9_CallsTarget) {
  ceres::internal::CovarianceImpl object{};
  object.ComputeCovarianceValuesUsingDenseSVD();
}
