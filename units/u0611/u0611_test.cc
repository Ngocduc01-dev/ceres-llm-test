// FILE: u0611_test.cc
#include "gtest/gtest.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/compressed_row_sparse_matrix.cc"

namespace ceres {
namespace internal {
// Path P1 calls TransposeForCompressedRowSparseStructure(const int num_rows, const int num_cols, const int num_nonzeros, const int * rows, const int * cols, const double * values, int * transpose_rows, int * transpose_cols, double * transpose_values).
TEST(Unitu0611, CallsTarget) {
  double rows_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double cols_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double values_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double transpose_rows_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double transpose_cols_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double transpose_values_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  TransposeForCompressedRowSparseStructure(1, 1, 1, rows_data, cols_data, values_data, transpose_rows_data, transpose_cols_data, transpose_values_data);
}
}  // namespace internal
}  // namespace ceres
