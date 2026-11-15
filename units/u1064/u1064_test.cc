// FILE: u1064_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1064, TC1_CallsTarget) {
  ceres::internal::FixedArray::Storage object{};
  object.InitializeData();
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1064, TC2_CallsTarget) {
  ceres::internal::FixedArray::Storage object{};
  object.InitializeData();
}
