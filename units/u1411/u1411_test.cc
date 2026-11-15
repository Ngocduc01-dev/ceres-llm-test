// FILE: u1411_test.cc
#include "gtest/gtest.h"
#include "ceres/solver.h"
#include "ceres/program.h"
#include "ceres/solver.cc"

// P1: START -> 1 -> END
TEST(u1411_Test, TC1_CallsTarget) {
  SummarizeGivenProgram(nullptr, nullptr);
}
