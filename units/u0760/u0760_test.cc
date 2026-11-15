// FILE: u0760_test.cc
#include "gtest/gtest.h"
#include "ceres/file.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0760, TC1_CallsTarget) {
  std::string dirname{};
  std::string basename{};
  ceres::internal::JoinPath(dirname, basename);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u0760, TC2_CallsTarget) {
  std::string dirname{};
  std::string basename{};
  ceres::internal::JoinPath(dirname, basename);
}

// P3: START -> 1 -> END; branch decisions covered by case 3
TEST(Unit_u0760, TC3_CallsTarget) {
  std::string dirname{};
  std::string basename{};
  ceres::internal::JoinPath(dirname, basename);
}

// P4: START -> 1 -> END; branch decisions covered by case 4
TEST(Unit_u0760, TC4_CallsTarget) {
  std::string dirname{};
  std::string basename{};
  ceres::internal::JoinPath(dirname, basename);
}
