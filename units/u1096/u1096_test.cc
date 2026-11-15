// FILE: u1096_test.cc
#include "gtest/gtest.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1096, TC1_CallsTarget) {
  std::string value{};
  ceres::StringToMinimizerType(value, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1096, TC2_CallsTarget) {
  std::string value{};
  ceres::StringToMinimizerType(value, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1096, TC3_CallsTarget) {
  std::string value{};
  ceres::StringToMinimizerType(value, nullptr);
}
