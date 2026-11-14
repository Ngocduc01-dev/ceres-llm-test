// u0524 – ceres::internal::SolveRTRWithSparseRHS
// Trích từ internal/ceres/compressed_col_sparse_matrix_utils.h, dòng 121–142 (chỉ để xem, không compile)

template <typename IntegerType>
void SolveRTRWithSparseRHS(IntegerType num_cols,
                           const IntegerType* rows,
                           const IntegerType* cols,
                           const double* values,
                           const int rhs_nonzero_index,
                           double* solution) {
  std::fill(solution, solution + num_cols, 0.0);
  solution[rhs_nonzero_index] = 1.0 / values[cols[rhs_nonzero_index + 1] - 1];

  for (IntegerType c = rhs_nonzero_index + 1; c < num_cols; ++c) {
    for (IntegerType idx = cols[c]; idx < cols[c + 1] - 1; ++idx) {
      const IntegerType r = rows[idx];
      if (r < rhs_nonzero_index) continue;
      const double v = values[idx];
      solution[c] -= v * solution[r];
    }
    solution[c] = solution[c] / values[cols[c + 1] - 1];
  }

  SolveUpperTriangularInPlace(num_cols, rows, cols, values, solution);
}
