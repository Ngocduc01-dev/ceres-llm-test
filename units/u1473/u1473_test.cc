// FILE: u1473_test.cc
#include "gtest/gtest.h"
#include "ceres/line_search_preprocessor.h"
#include "ceres/program.h"
#include "ceres/line_search_preprocessor.cc"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1473, TC1_CallsTarget) {
  Program program{};
  ceres::internal::(anonymous)::IsProgramValid(program, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1473, TC2_CallsTarget) {
  Program program{};
  ceres::internal::(anonymous)::IsProgramValid(program, nullptr);
}
