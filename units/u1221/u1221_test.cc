// FILE: u1221_test.cc
#include "gtest/gtest.h"
#include "ceres/block_structure.h"
#include "ceres/linear_solver.h"
#include "ceres/schur_eliminator.h"
#include "ceres/schur_jacobi_preconditioner.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1221, TC1_CallsTarget) {
  CompressedRowBlockStructure bs{};
  ceres::internal::SchurJacobiPreconditioner object{};
  object.InitEliminator(bs);
}
