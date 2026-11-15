// FILE: u1032_test.cc
#include "gtest/gtest.h"
#include "ceres/implicit_schur_complement.h"
#include "ceres/parallel_vector_ops.h"
#include "ceres/partitioned_matrix_view.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1032, TC1_CallsTarget) {
  ceres::internal::ImplicitSchurComplement object{};
  object.RightMultiplyAndAccumulate(nullptr, nullptr);
}

// P2: START -> 1 -> END; branch decisions covered by case 2
TEST(Unit_u1032, TC2_CallsTarget) {
  ceres::internal::ImplicitSchurComplement object{};
  object.RightMultiplyAndAccumulate(nullptr, nullptr);
}
