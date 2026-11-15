// FILE: u1225_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/block_structure.h"
#include "ceres/implicit_schur_complement.h"
#include "ceres/parallel_for.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1225, TC1_CallsTarget) {
  ceres::internal::ImplicitSchurComplement object{};
  object.AddDiagonalAndInvert(nullptr, nullptr);
}
