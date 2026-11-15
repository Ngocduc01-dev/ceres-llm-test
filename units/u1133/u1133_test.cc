// FILE: u1133_test.cc
#include "gtest/gtest.h"
#include "ceres/block_random_access_sparse_matrix.h"
#include "ceres/block_structure.h"
#include "ceres/visibility_based_preconditioner.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1133, TC1_CallsTarget) {
  CompressedRowBlockStructure bs{};
  ceres::internal::VisibilityBasedPreconditioner object{};
  object.InitStorage(bs);
}
