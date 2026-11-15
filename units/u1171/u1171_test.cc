// FILE: u1171_test.cc
#include "gtest/gtest.h"
#include "ceres/line_search.h"

// P1: START -> 1 -> END
TEST(CreateTest, TC1_CallsTarget) {
  LineSearch object{};
  LineSearchType a0{};
  LineSearch::Options & options a1{};
  object.Create(a0, a1, nullptr);
}

// P2: START -> 1 -> END
TEST(CreateTest, TC2_CallsTarget) {
  LineSearch object{};
  LineSearchType a0{};
  LineSearch::Options & options a1{};
  object.Create(a0, a1, nullptr);
}

