// FILE: u0895_test.cc
#include "gtest/gtest.h"
#include "ceres/context_impl.h"
#include "ceres/sparse_matrix.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0895, TC1_CallsTarget) {
  int num_threads{};
  ceres::internal::SparseMatrix object{};
  object.ScaleColumns(nullptr, nullptr, num_threads);
}
