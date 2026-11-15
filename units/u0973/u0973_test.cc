// FILE: u0973_test.cc
#include "gtest/gtest.h"
#include "ceres/solver.h"
#include "ceres/evaluator.h"
#include "ceres/minimizer.h"
#include "ceres/trust_region_minimizer.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0973, TC1_CallsTarget) {
  Minimizer::Options options{};
  ceres::internal::TrustRegionMinimizer object{};
  object.Init(options, nullptr, nullptr);
}
