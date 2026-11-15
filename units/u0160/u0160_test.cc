// FILE: u0160_test.cc
#include "gtest/gtest.h"
#include "ceres/jet.h"

// P1: START -> 1 -> END (không có điểm rẽ nhánh)
TEST(NumTraitsJetDummyPrecision, P1_ReturnsJet) {
  Eigen::NumTraits<ceres::Jet<double, 2>> obj;
  auto result = obj.dummy_precision();
  (void)result;  // Không kiểm tra kết quả trả về
}
