// FILE: u0173_test.cc
#include "gtest/gtest.h"
#include "ceres/loss_function.h"

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(SoftLOneLossConstructorTest, TC1_P1_SingleStraightPath) {
  const double a = 3.7;  // giá trị cố định trong khoảng (0, 10]
  ceres::SoftLOneLoss loss(a);
  (void)loss;  // không kiểm tra kết quả
}
