// FILE: u0783_test.cc
#include "gtest/gtest.h"
#include "ceres/reorder_program.h"

// P1: START -> 1 -> END
TEST(AreJacobianColumnsOrderedTest, TC1_CallsTarget) {
  LinearSolverType a0{};
  PreconditionerType a1{};
  SparseLinearAlgebraLibraryType a2{};
  LinearSolverOrderingType a3{};
  ceres::internal::AreJacobianColumnsOrdered(a0, a1, a2, a3);
}

// P2: START -> 1 -> END
TEST(AreJacobianColumnsOrderedTest, TC2_CallsTarget) {
  LinearSolverType a0{};
  PreconditionerType a1{};
  SparseLinearAlgebraLibraryType a2{};
  LinearSolverOrderingType a3{};
  ceres::internal::AreJacobianColumnsOrdered(a0, a1, a2, a3);
}

// P3: START -> 1 -> END
TEST(AreJacobianColumnsOrderedTest, TC3_CallsTarget) {
  LinearSolverType a0{};
  PreconditionerType a1{};
  SparseLinearAlgebraLibraryType a2{};
  LinearSolverOrderingType a3{};
  ceres::internal::AreJacobianColumnsOrdered(a0, a1, a2, a3);
}

