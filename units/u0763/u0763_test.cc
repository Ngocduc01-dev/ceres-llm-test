// FILE: u0763_test.cc
#include "gtest/gtest.h"
#include "ceres/line_search_direction.h"

// P1: START -> 1 -> END
TEST(CreateTest, TC1_CallsTarget) {
  LineSearchDirection object{};
  LineSearchDirection::Options & options a0{};
  object.Create(a0);
}

// P2: START -> 1 -> END
TEST(CreateTest, TC2_CallsTarget) {
  LineSearchDirection object{};
  LineSearchDirection::Options & options a0{};
  object.Create(a0);
}

// P3: START -> 1 -> END
TEST(CreateTest, TC3_CallsTarget) {
  LineSearchDirection object{};
  LineSearchDirection::Options & options a0{};
  object.Create(a0);
}

