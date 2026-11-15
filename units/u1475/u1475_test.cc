// FILE: u1475_test.cc
#include "gtest/gtest.h"
#include "ceres/trust_region_preprocessor.h"
#include "ceres/program.h"
#include "ceres/trust_region_preprocessor.cc"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1475, TC1_CallsTarget) {
  Program program{};
  ceres::internal::(anonymous)::IsProgramValid(program, nullptr);
}
