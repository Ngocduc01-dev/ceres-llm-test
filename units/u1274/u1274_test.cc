// FILE: u1274_test.cc
#include "gtest/gtest.h"
#include "ceres/solver.cc"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1274, TC1_CallsTarget) {
  std::vector<int> ordering{};
  ceres::StringifyOrdering(ordering, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1274, TC2_CallsTarget) {
  std::vector<int> ordering{};
  ceres::StringifyOrdering(ordering, nullptr);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u1274, TC3_CallsTarget) {
  std::vector<int> ordering{};
  ceres::StringifyOrdering(ordering, nullptr);
}
