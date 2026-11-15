// FILE: u0832_test.cc
#include "gtest/gtest.h"
#include "ceres/problem.h"

// P1: START -> 1 -> END
TEST(ceres_free_problemTest, TC1_CallsTarget) {
  ceres_free_problem(nullptr);
}

