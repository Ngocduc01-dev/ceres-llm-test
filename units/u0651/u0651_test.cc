// FILE: u0651_test.cc
#include "gtest/gtest.h"
#include "ceres/block_sparse_matrix.h"
#include "ceres/block_structure.h"

// Path P1 calls BlockSparseMatrixData(const CompressedRowBlockStructure * block_structure, const double * values).
TEST(Unitu0651, CallsTarget) {
  double block_structure_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double values_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  object.BlockSparseMatrixData(block_structure_data, values_data);
}
