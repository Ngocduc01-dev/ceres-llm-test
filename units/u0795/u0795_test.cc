// FILE: u0795_test.cc
#include "gtest/gtest.h"
#include "ceres/block_random_access_matrix.h"
#include "ceres/schur_complement_solver.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0795, TC1_CallsTarget) {
  ceres::internal::SchurComplementSolver object{};
  object.lhs();
}
