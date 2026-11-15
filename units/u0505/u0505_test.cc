// FILE: u0505_test.cc
#include "gtest/gtest.h"
#include "ceres/compressed_col_sparse_matrix_utils.h"

namespace ceres {
namespace internal {
// Path P1 calls SolveUpperTriangularTransposeInPlace(IntegerType num_cols, const IntegerType* rows, const IntegerType* cols, const double* values, double* rhs_and_solution).
TEST(Unitu0505, CallsTarget) {
  double rows_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double cols_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double values_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  double rhs_and_solution_data = {1.0, 2.0, 3.0, 4.0, 5.0};
  SolveUpperTriangularTransposeInPlace(1, rows_data, cols_data, values_data, rhs_and_solution_data);
}
}  // namespace internal
}  // namespace ceres
