// FILE: u1064_test.cc
#include "gtest/gtest.h"
#include "ceres/internal/fixed_array.h"

// P1: START -> 1 -> END
TEST(InitializeDataTest, TC1_CallsTarget) {
  Storage object{};
  object.InitializeData();
}

// P2: START -> 1 -> END
TEST(InitializeDataTest, TC2_CallsTarget) {
  Storage object{};
  object.InitializeData();
}

