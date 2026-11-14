// u0839 – ceres::internal::CompressedRowSparseMatrix::ToCRSMatrix
// Trích từ internal/ceres/compressed_row_sparse_matrix.cc, dòng 539–550 (chỉ để xem, không compile)

void CompressedRowSparseMatrix::ToCRSMatrix(CRSMatrix* matrix) const {
  matrix->num_rows = num_rows_;
  matrix->num_cols = num_cols_;
  matrix->rows = rows_;
  matrix->cols = cols_;
  matrix->values = values_;

  // Trim.
  matrix->rows.resize(matrix->num_rows + 1);
  matrix->cols.resize(matrix->rows[matrix->num_rows]);
  matrix->values.resize(matrix->rows[matrix->num_rows]);
}
