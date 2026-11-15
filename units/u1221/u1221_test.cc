// FILE: u1221_test.cc
#include "gtest/gtest.h"
#include "ceres/block_structure.h"
#include "ceres/linear_solver.h"
#include "ceres/schur_eliminator.h"
#include "ceres/schur_jacobi_preconditioner.h"

// P1: START -> 1 -> END
TEST(InitEliminatorTest, TC1_CallsTarget) {
  SchurJacobiPreconditioner object{};
  CompressedRowBlockStructure & bs a0{};
  object.InitEliminator(a0);
}

