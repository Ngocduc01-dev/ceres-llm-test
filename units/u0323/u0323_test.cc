// FILE: u0323_test.cc
#include "gtest/gtest.h"
#include "ceres/levenberg_marquardt_strategy.h"

// P1: START -> 1 -> END (không có nhánh rẽ)
TEST(LevenbergMarquardtStrategyRadiusTest, TC1_ReturnRadius) {
  ceres::internal::TrustRegionStrategy::Options options;
  options.initial_radius = 5000.0;
  ceres::internal::LevenbergMarquardtStrategy strategy(options);
  double r = strategy.Radius();
  (void)r;  // Không kiểm tra kết quả trả về
}
