// FILE: u0071_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(JetConstructorDenseBaseTest, TC1_ScalarAndDenseVector) {
  using JetType = ceres::Jet<double, 4>;
  Eigen::Matrix<double, 4, 1> v;
  v << 1.5, -2.0, 0.5, 4.0;
  const double a = 3.5;
  JetType j(a, v);
  (void)j;
}
