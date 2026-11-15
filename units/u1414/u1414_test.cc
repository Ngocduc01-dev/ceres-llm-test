// FILE: u1414_test.cc
#include "gtest/gtest.h"
#include "ceres/solver.h"
#include "ceres/solver.cc"

// P1: START -> 1 -> END
TEST(u1414_Test, TC1_CallsTarget) {
  OptionsAreValidForSparseNormalCholesky(nullptr, nullptr);
}
