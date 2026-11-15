// FILE: u1162_test.cc
#include "gtest/gtest.h"
#include "ceres/iterative_refiner.h"
#include "ceres/sparse_cholesky.h"
#include "ceres/sparse_matrix.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1162, TC1_CallsTarget) {
  SparseMatrix lhs{};
  ceres::internal::SparseIterativeRefiner object{};
  object.Refine(lhs, nullptr, nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1162, TC2_CallsTarget) {
  SparseMatrix lhs{};
  ceres::internal::SparseIterativeRefiner object{};
  object.Refine(lhs, nullptr, nullptr, nullptr);
}
