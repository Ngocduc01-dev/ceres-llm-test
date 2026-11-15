// FILE: u0164_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(NumTraitsJetHighest, TC1_P1_ReturnHighest) {
  Eigen::NumTraits<ceres::Jet<double, 2>> obj;
  obj.highest();
}
