// FILE: u1060_test.cc
#include "gtest/gtest.h"
#include "ceres/small_blas.h"
#include "ceres/small_blas_generic.h"

// P1: START -> 1 -> END
TEST(MatrixTransposeVectorMultiplyTest, TC1_CallsTarget) {
  double a0[5] = {};
  int a1 = 0;
  int a2 = 0;
  double a3[5] = {};
  double a4[5] = {};
  ceres::internal::MatrixTransposeVectorMultiply(a0, a1, a2, a3, a4);
}

// P2: START -> 1 -> END
TEST(MatrixTransposeVectorMultiplyTest, TC2_CallsTarget) {
  double a0[5] = {};
  int a1 = 0;
  int a2 = 0;
  double a3[5] = {};
  double a4[5] = {};
  ceres::internal::MatrixTransposeVectorMultiply(a0, a1, a2, a3, a4);
}

// P3: START -> 1 -> END
TEST(MatrixTransposeVectorMultiplyTest, TC3_CallsTarget) {
  double a0[5] = {};
  int a1 = 0;
  int a2 = 0;
  double a3[5] = {};
  double a4[5] = {};
  ceres::internal::MatrixTransposeVectorMultiply(a0, a1, a2, a3, a4);
}

