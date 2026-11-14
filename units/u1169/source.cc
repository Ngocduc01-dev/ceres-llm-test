// u1169 – ceres::internal::CompressedRowSparseMatrix::RightMultiplyAndAccumulate
// Trích từ internal/ceres/compressed_row_sparse_matrix.cc, dòng 283–302 (chỉ để xem, không compile)

void CompressedRowSparseMatrix::RightMultiplyAndAccumulate(
    const double* x, double* y, ContextImpl* context, int num_threads) const {
  if (storage_type_ != StorageType::UNSYMMETRIC) {
    RightMultiplyAndAccumulate(x, y);
    return;
  }

  auto values = values_.data();
  auto rows = rows_.data();
  auto cols = cols_.data();

  ParallelFor(
      context, 0, num_rows_, num_threads, [values, rows, cols, x, y](int row) {
        for (int idx = rows[row]; idx < rows[row + 1]; ++idx) {
          const int c = cols[idx];
          const double v = values[idx];
          y[row] += v * x[c];
        }
      });
}
