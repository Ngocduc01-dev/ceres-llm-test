// u1149 – ceres::internal::DynamicCompressedRowSparseMatrix::DynamicCompressedRowSparseMatrix
// Trích từ internal/ceres/dynamic_compressed_row_sparse_matrix.cc, dòng 37–42 (chỉ để xem, không compile)

DynamicCompressedRowSparseMatrix::DynamicCompressedRowSparseMatrix(
    int num_rows, int num_cols, int initial_max_num_nonzeros)
    : CompressedRowSparseMatrix(num_rows, num_cols, initial_max_num_nonzeros) {
  dynamic_cols_.resize(num_rows);
  dynamic_values_.resize(num_rows);
}
