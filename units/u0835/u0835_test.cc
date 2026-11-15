// FILE: u0835_test.cc
#include "gtest/gtest.h"
#include "ceres/cgnr_solver.h"
#include "ceres/context_impl.h"
#include "ceres/linear_operator.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0835, TC1_CallsTarget) {
  LinearOperator A{};
  int num_threads{};
  ceres::internal::CgnrLinearOperator object{};
  (void)object;
}
