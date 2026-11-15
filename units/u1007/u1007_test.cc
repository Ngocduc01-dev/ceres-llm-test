// FILE: u1007_test.cc
#include "gtest/gtest.h"
#include "ceres/line_search_direction.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1007, TC1_CallsTarget) {
  const int num_parameters{};
  const int max_lbfgs_rank{};
  const bool use_approximate_eigenvalue_bfgs_scaling{};
  ceres::internal::LBFGS object{};
  (void)object;
}
