// FILE: u1479_test.cc
#include "gtest/gtest.h"
#include "ceres/block_structure.h"
#include "ceres/graph_algorithms.h"
#include "ceres/visibility.h"
#include "ceres/visibility_based_preconditioner.h"

// P1: START -> 1 -> END; branch decisions covered by case 1
TEST(Unit_u1479, TC1_CallsTarget) {
  CompressedRowBlockStructure bs{};
  ceres::internal::VisibilityBasedPreconditioner object{};
  object.ComputeClusterTridiagonalSparsity(bs);
}
