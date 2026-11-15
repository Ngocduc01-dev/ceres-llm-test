// FILE: u1413_test.cc
#include "gtest/gtest.h"
#include "ceres/solver.h"
#include "ceres/solver.cc"

// P1: START -> 1 -> END
TEST(u1413_Test, TC1_CallsTarget) {
  OptionsAreValidForDenseNormalCholesky(nullptr, nullptr);
}
