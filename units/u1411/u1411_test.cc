// FILE: u1411_test.cc
#include "gtest/gtest.h"
#include "ceres/solver.h"
#include "ceres/program.h"
#include "ceres/solver.cc"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1411, TC1_CallsTarget) {
  internal::Program program{};
  ceres::SummarizeGivenProgram(program, nullptr);
}
