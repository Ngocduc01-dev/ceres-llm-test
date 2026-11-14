// u0505 – ceres::internal::SolveUpperTriangularTransposeInPlace
// Trích từ internal/ceres/compressed_col_sparse_matrix_utils.h, dòng 95–109 (chỉ để xem, không compile)

template <typename IntegerType>
void SolveUpperTriangularTransposeInPlace(IntegerType num_cols,
                                          const IntegerType* rows,
                                          const IntegerType* cols,
                                          const double* values,
                                          double* rhs_and_solution) {
  for (IntegerType c = 0; c < num_cols; ++c) {
    for (IntegerType idx = cols[c]; idx < cols[c + 1] - 1; ++idx) {
      const IntegerType r = rows[idx];
      const double v = values[idx];
      rhs_and_solution[c] -= v * rhs_and_solution[r];
    }
    rhs_and_solution[c] = rhs_and_solution[c] / values[cols[c + 1] - 1];
  }
}
