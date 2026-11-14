// u0917 – ceres::internal::CompressedRowSparseMatrix::CompressedRowSparseMatrix
// Trích từ internal/ceres/compressed_row_sparse_matrix.cc, dòng 164–179 (chỉ để xem, không compile)

CompressedRowSparseMatrix::CompressedRowSparseMatrix(int num_rows,
                                                     int num_cols,
                                                     int max_num_nonzeros) {
  num_rows_ = num_rows;
  num_cols_ = num_cols;
  storage_type_ = StorageType::UNSYMMETRIC;
  rows_.resize(num_rows + 1, 0);
  cols_.resize(max_num_nonzeros, 0);
  values_.resize(max_num_nonzeros, 0.0);

  VLOG(1) << "# of rows: " << num_rows_ << " # of columns: " << num_cols_
          << " max_num_nonzeros: " << cols_.size() << ". Allocating "
          << (num_rows_ + 1) * sizeof(int) +     // NOLINT
                 cols_.size() * sizeof(int) +    // NOLINT
                 cols_.size() * sizeof(double);  // NOLINT
}
