// FILE: u0204_test.cc
#include "gtest/gtest.h"
#include "ceres/rotation.h"

// Path P1: START -> 1 -> END (hàm không có điểm rẽ nhánh)
TEST(MatrixAdapterOperatorCall, P1_SingleStatement) {
  const double data[5] = {1.5, 2.5, 3.5, 4.5, 5.5};
  ceres::MatrixAdapter<const double, 1, 3> m(data);
  const double& value = m(1, 1);
  (void)value;
}
