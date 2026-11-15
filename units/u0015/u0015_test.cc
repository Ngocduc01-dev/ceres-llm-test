// FILE: u0015_test.cc
#include "gtest/gtest.h"
#include "ceres/crs_matrix.h"

// Path: P1 (START -> 1 -> END), không có điểm rẽ nhánh
TEST(CRSMatrixConstructorTest, DefaultConstructor) {
  ceres::CRSMatrix matrix;
  (void)matrix;
}
