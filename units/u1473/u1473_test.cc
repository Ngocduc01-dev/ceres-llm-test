// FILE: u1473_test.cc
#include "gtest/gtest.h"
#include "ceres/line_search_preprocessor.h"
#include "ceres/program.h"
#include "ceres/line_search_preprocessor.cc"

// P1: START -> 1 -> END
TEST(u1473_Test, TC1_CallsTarget) {
  IsProgramValid(nullptr, nullptr);
}

// P2: START -> 1 -> END
TEST(u1473_Test, TC2_CallsTarget) {
  IsProgramValid(nullptr, nullptr);
}
