// FILE: u1475_test.cc
#include "gtest/gtest.h"
#include "ceres/trust_region_preprocessor.h"
#include "ceres/program.h"
#include "ceres/trust_region_preprocessor.cc"

// P1: START -> 1 -> END
TEST(u1475_Test, TC1_CallsTarget) {
  IsProgramValid(nullptr, nullptr);
}
