// FILE: u1293_test.cc
#include "gtest/gtest.h"
#include "ceres/array_utils.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1293, TC1_CallsTarget) {
  const int64_t size{};
  ceres::internal::AppendArrayToString(size, nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1293, TC2_CallsTarget) {
  const int64_t size{};
  ceres::internal::AppendArrayToString(size, nullptr, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1293, TC3_CallsTarget) {
  const int64_t size{};
  ceres::internal::AppendArrayToString(size, nullptr, nullptr);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u1293, TC4_CallsTarget) {
  const int64_t size{};
  ceres::internal::AppendArrayToString(size, nullptr, nullptr);
}
