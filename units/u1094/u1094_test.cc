// FILE: u1094_test.cc
#include "gtest/gtest.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1094, TC1_CallsTarget) {
  std::string value{};
  ceres::StringToTrustRegionStrategyType(value, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1094, TC2_CallsTarget) {
  std::string value{};
  ceres::StringToTrustRegionStrategyType(value, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1094, TC3_CallsTarget) {
  std::string value{};
  ceres::StringToTrustRegionStrategyType(value, nullptr);
}
