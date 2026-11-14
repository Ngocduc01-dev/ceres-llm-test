// u1114 – ceres::internal::DynamicCompressedRowSparseMatrix::InsertEntry
// Trích từ internal/ceres/dynamic_compressed_row_sparse_matrix.cc, dòng 44–53 (chỉ để xem, không compile)

void DynamicCompressedRowSparseMatrix::InsertEntry(int row,
                                                   int col,
                                                   const double& value) {
  CHECK_GE(row, 0);
  CHECK_LT(row, num_rows());
  CHECK_GE(col, 0);
  CHECK_LT(col, num_cols());
  dynamic_cols_[row].push_back(col);
  dynamic_values_[row].push_back(value);
}
