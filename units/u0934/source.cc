// u0934 – ceres::internal::CompressedRowSparseMatrix::ToTextFile
// Trích từ internal/ceres/compressed_row_sparse_matrix.cc, dòng 530–537 (chỉ để xem, không compile)

void CompressedRowSparseMatrix::ToTextFile(FILE* file) const {
  CHECK(file != nullptr);
  for (int r = 0; r < num_rows_; ++r) {
    for (int idx = rows_[r]; idx < rows_[r + 1]; ++idx) {
      fprintf(file, "% 10d % 10d %17f\n", r, cols_[idx], values_[idx]);
    }
  }
}
