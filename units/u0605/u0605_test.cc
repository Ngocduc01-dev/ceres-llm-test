// FILE: u0605_test.cc
#include "gtest/gtest.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/compressed_row_sparse_matrix.cc"

namespace ceres {
namespace internal {
// Path P1 calls AddRandomBlock(const int num_rows, const int num_cols, const int row_block_begin, const int col_block_begin, RandomNormalFunctor&& randn, std::vector<int>* rows, std::vector<int>* cols, std::vector<double>* values).
TEST(Unitu0605, CallsTarget) {
  double rows_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double cols_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double values_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  AddRandomBlock(1, 1, 1, 1, {}, rows_data, cols_data, values_data);
}
}  // namespace internal
}  // namespace ceres
