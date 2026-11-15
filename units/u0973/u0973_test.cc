// FILE: u0973_test.cc
#include "gtest/gtest.h"
#include "ceres/solver.h"
#include "ceres/evaluator.h"
#include "ceres/minimizer.h"
#include "ceres/trust_region_minimizer.h"

// P1: START -> 1 -> END
TEST(InitTest, TC1_CallsTarget) {
  TrustRegionMinimizer object{};
  Minimizer::Options & options a0{};
  double a1[5] = {};
  object.Init(a0, a1, nullptr);
}

