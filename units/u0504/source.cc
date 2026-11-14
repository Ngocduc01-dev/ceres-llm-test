// u0504 – ceres::internal::SolveUpperTriangularInPlace
// Trích từ internal/ceres/compressed_col_sparse_matrix_utils.h, dòng 74–88 (chỉ để xem, không compile)

template <typename IntegerType>
void SolveUpperTriangularInPlace(IntegerType num_cols,
                                 const IntegerType* rows,
                                 const IntegerType* cols,
                                 const double* values,
                                 double* rhs_and_solution) {
  for (IntegerType c = num_cols - 1; c >= 0; --c) {
    rhs_and_solution[c] /= values[cols[c + 1] - 1];
    for (IntegerType idx = cols[c]; idx < cols[c + 1] - 1; ++idx) {
      const IntegerType r = rows[idx];
      const double v = values[idx];
      rhs_and_solution[r] -= v * rhs_and_solution[c];
    }
  }
}
