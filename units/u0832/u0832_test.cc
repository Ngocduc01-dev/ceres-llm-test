// FILE: u0832_test.cc
#include "gtest/gtest.h"
#include "ceres/problem.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0832, TC1_CallsTarget) {
  ceres_free_problem(nullptr);
}
