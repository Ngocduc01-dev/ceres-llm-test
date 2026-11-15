// FILE: u0606_test.cc
#include "gtest/gtest.h"
#include "ceres/compressed_row_sparse_matrix.h"
#include "ceres/compressed_row_sparse_matrix.cc"

namespace ceres {
namespace internal {
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0606, CallsTarget) {
  double rows_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double cols_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double values_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  AddSymmetricRandomBlock(1, 1, {}, rows_data, cols_data, values_data);
}
}  // namespace internal
}  // namespace ceres
