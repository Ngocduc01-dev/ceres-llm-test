// u1182 – ceres::internal::CompressedRowSparseMatrix::CompressedRowSparseMatrix
// Trích từ internal/ceres/compressed_row_sparse_matrix.cc, dòng 254–273 (chỉ để xem, không compile)

CompressedRowSparseMatrix::CompressedRowSparseMatrix(const double* diagonal,
                                                     int num_rows) {
  CHECK(diagonal != nullptr);

  num_rows_ = num_rows;
  num_cols_ = num_rows;
  storage_type_ = StorageType::UNSYMMETRIC;
  rows_.resize(num_rows + 1);
  cols_.resize(num_rows);
  values_.resize(num_rows);

  rows_[0] = 0;
  for (int i = 0; i < num_rows_; ++i) {
    cols_[i] = i;
    values_[i] = diagonal[i];
    rows_[i + 1] = i + 1;
  }

  CHECK_EQ(num_nonzeros(), num_rows);
}
