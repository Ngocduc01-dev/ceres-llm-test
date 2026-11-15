// FILE: u0810_test.cc
#include "gtest/gtest.h"
#include "ceres/linear_least_squares_problems.h"
#include "ceres/linear_least_squares_problems.cc"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0810, TC1_CallsTarget) {
  std::string filename{};
  const int size{};
  ceres::internal::(anonymous)::WriteArrayToFileOrDie(filename, nullptr, size);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u0810, TC2_CallsTarget) {
  std::string filename{};
  const int size{};
  ceres::internal::(anonymous)::WriteArrayToFileOrDie(filename, nullptr, size);
}
