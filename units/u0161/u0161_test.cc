// FILE: u0161_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// Path P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(NumTraitsEpsilon, TC1_P1_JetDoubleN2) {
  Eigen::NumTraits<ceres::Jet<double, 2>> obj;
  (void)obj.epsilon();
}
