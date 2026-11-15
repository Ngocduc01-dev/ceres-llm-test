// FILE: u0921_test.cc
#include "gtest/gtest.h"
#include "ceres/line_search_minimizer.h"
#include "ceres/minimizer.h"
#include "ceres/trust_region_minimizer.h"

// P1: START -> 1 -> END
TEST(CreateTest, TC1_CallsTarget) {
  Minimizer object{};
  MinimizerType a0{};
  object.Create(a0);
}

// P2: START -> 1 -> END
TEST(CreateTest, TC2_CallsTarget) {
  Minimizer object{};
  MinimizerType a0{};
  object.Create(a0);
}

