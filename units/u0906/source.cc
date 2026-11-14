// u0906 – ceres::internal::CompressedRowSparseMatrix::SetMaxNumNonZeros
// Trích từ internal/ceres/compressed_row_sparse_matrix.cc, dòng 552–557 (chỉ để xem, không compile)

void CompressedRowSparseMatrix::SetMaxNumNonZeros(int num_nonzeros) {
  CHECK_GE(num_nonzeros, 0);

  cols_.resize(num_nonzeros);
  values_.resize(num_nonzeros);
}
