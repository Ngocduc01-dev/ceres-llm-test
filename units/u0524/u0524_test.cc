// FILE: u0524_test.cc
#include "gtest/gtest.h"
#include "ceres/compressed_col_sparse_matrix_utils.h"

namespace ceres {
namespace internal {
// Path P1: START -> CFG nodes -> END.
TEST(Unit_u0524, CallsTarget) {
  double rows_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double cols_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double values_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double solution_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  SolveRTRWithSparseRHS(1, rows_data, cols_data, values_data, 1, solution_data);
}
}  // namespace internal
}  // namespace ceres
