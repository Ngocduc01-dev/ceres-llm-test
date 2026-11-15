// FILE: u0921_test.cc
#include "gtest/gtest.h"
#include "ceres/line_search_minimizer.h"
#include "ceres/minimizer.h"
#include "ceres/trust_region_minimizer.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0921, TC1_CallsTarget) {
  MinimizerType minimizer_type{};
  ceres::internal::Minimizer object{};
  object.Create(minimizer_type);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u0921, TC2_CallsTarget) {
  MinimizerType minimizer_type{};
  ceres::internal::Minimizer object{};
  object.Create(minimizer_type);
}
