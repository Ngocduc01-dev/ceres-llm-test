// u1216 – ceres::internal::CompressedRowSparseMatrix::SquaredColumnNorm
// Trích từ internal/ceres/compressed_row_sparse_matrix.cc, dòng 378–433 (chỉ để xem, không compile)

void CompressedRowSparseMatrix::SquaredColumnNorm(double* x) const {
  CHECK(x != nullptr);

  std::fill(x, x + num_cols_, 0.0);
  if (storage_type_ == StorageType::UNSYMMETRIC) {
    for (int idx = 0; idx < rows_[num_rows_]; ++idx) {
      x[cols_[idx]] += values_[idx] * values_[idx];
    }
  } else if (storage_type_ == StorageType::UPPER_TRIANGULAR) {
    // Because of their block structure, we will have entries that lie
    // above (below) the diagonal for lower (upper) triangular
    // matrices, so the loops below need to account for this.
    for (int r = 0; r < num_rows_; ++r) {
      int idx = rows_[r];
      const int idx_end = rows_[r + 1];

      // For upper triangular matrices r <= c, so skip entries with r
      // > c.
      while (idx < idx_end && r > cols_[idx]) {
        ++idx;
      }

      for (; idx < idx_end; ++idx) {
        const int c = cols_[idx];
        const double v2 = values_[idx] * values_[idx];
        x[c] += v2;
        // Since we are only iterating over the upper triangular part
        // of the matrix, add contributions for the strictly lower
        // triangular part.
        if (r != c) {
          x[r] += v2;
        }
      }
    }
  } else if (storage_type_ == StorageType::LOWER_TRIANGULAR) {
    for (int r = 0; r < num_rows_; ++r) {
      int idx = rows_[r];
      const int idx_end = rows_[r + 1];
      // For lower triangular matrices, we only iterate till we are r >=
      // c.
      for (; idx < idx_end && r >= cols_[idx]; ++idx) {
        const int c = cols_[idx];
        const double v2 = values_[idx] * values_[idx];
        x[c] += v2;
        // Since we are only iterating over the lower triangular part
        // of the matrix, add contributions for the strictly upper
        // triangular part.
        if (r != c) {
          x[r] += v2;
        }
      }
    }
  } else {
    LOG(FATAL) << "Unknown storage type: " << storage_type_;
  }
}
