// FILE: u0779_test.cc
#include "gtest/gtest.h"
#include "ceres/line_search_direction.h"
#include "ceres/line_search_minimizer.h"

// P1: START -> 1 -> END
TEST(NextDirectionTest, TC1_CallsTarget) {
  BFGS object{};
  LineSearchMinimizer::State & previous a0{};
  LineSearchMinimizer::State & current a1{};
  object.NextDirection(a0, a1, nullptr);
}

// P2: START -> 1 -> END
TEST(NextDirectionTest, TC2_CallsTarget) {
  BFGS object{};
  LineSearchMinimizer::State & previous a0{};
  LineSearchMinimizer::State & current a1{};
  object.NextDirection(a0, a1, nullptr);
}

// P3: START -> 1 -> END
TEST(NextDirectionTest, TC3_CallsTarget) {
  BFGS object{};
  LineSearchMinimizer::State & previous a0{};
  LineSearchMinimizer::State & current a1{};
  object.NextDirection(a0, a1, nullptr);
}

