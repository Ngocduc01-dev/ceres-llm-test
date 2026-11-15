// FILE: u1217_test.cc
#include "gtest/gtest.h"
#include "ceres/manifold.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/covariance_impl.h"
#include "ceres/map_util.h"
#include "ceres/parameter_block.h"
#include "ceres/problem_impl.h"

// P1: START -> 1 -> END
TEST(GetCovarianceBlockInTangentOrAmbientSpaceTest, TC1_CallsTarget) {
  CovarianceImpl object{};
  double a0[5] = {};
  double a1[5] = {};
  bool a2 = false;
  double a3[5] = {};
  object.GetCovarianceBlockInTangentOrAmbientSpace(a0, a1, a2, a3);
}

// P2: START -> 1 -> END
TEST(GetCovarianceBlockInTangentOrAmbientSpaceTest, TC2_CallsTarget) {
  CovarianceImpl object{};
  double a0[5] = {};
  double a1[5] = {};
  bool a2 = false;
  double a3[5] = {};
  object.GetCovarianceBlockInTangentOrAmbientSpace(a0, a1, a2, a3);
}

// P3: START -> 1 -> END
TEST(GetCovarianceBlockInTangentOrAmbientSpaceTest, TC3_CallsTarget) {
  CovarianceImpl object{};
  double a0[5] = {};
  double a1[5] = {};
  bool a2 = false;
  double a3[5] = {};
  object.GetCovarianceBlockInTangentOrAmbientSpace(a0, a1, a2, a3);
}

