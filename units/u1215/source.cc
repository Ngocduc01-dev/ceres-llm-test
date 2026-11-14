// u1215 – ceres::internal::CompressedRowSparseMatrix::RightMultiplyAndAccumulate
// Trích từ internal/ceres/compressed_row_sparse_matrix.cc, dòng 304–358 (chỉ để xem, không compile)

void CompressedRowSparseMatrix::RightMultiplyAndAccumulate(const double* x,
                                                           double* y) const {
  CHECK(x != nullptr);
  CHECK(y != nullptr);

  if (storage_type_ == StorageType::UNSYMMETRIC) {
    RightMultiplyAndAccumulate(x, y, nullptr, 1);
  } else if (storage_type_ == StorageType::UPPER_TRIANGULAR) {
    // Because of their block structure, we will have entries that lie
    // above (below) the diagonal for lower (upper) triangular matrices,
    // so the loops below need to account for this.
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
        const double v = values_[idx];
        y[r] += v * x[c];
        // Since we are only iterating over the upper triangular part
        // of the matrix, add contributions for the strictly lower
        // triangular part.
        if (r != c) {
          y[c] += v * x[r];
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
        const double v = values_[idx];
        y[r] += v * x[c];
        // Since we are only iterating over the lower triangular part
        // of the matrix, add contributions for the strictly upper
        // triangular part.
        if (r != c) {
          y[c] += v * x[r];
        }
      }
    }
  } else {
    LOG(FATAL) << "Unknown storage type: " << storage_type_;
  }
}
