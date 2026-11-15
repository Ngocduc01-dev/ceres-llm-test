// FILE: u0896_test.cc
#include "gtest/gtest.h"
#include "ceres/context_impl.h"
#include "ceres/sparse_matrix.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u0896, TC1_CallsTarget) {
   int{};
  ceres::internal::SparseMatrix object{};
  object.SetZero(nullptr, int);
}
