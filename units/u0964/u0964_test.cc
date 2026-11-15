// FILE: u0964_test.cc
#include "gtest/gtest.h"
#include "ceres/linear_solver.h"
#include "ceres/schur_complement_solver.h"

// P1: START -> 1 -> END
TEST(optionsTest, TC1_CallsTarget) {
  SchurComplementSolver object{};
  object.options();
}

