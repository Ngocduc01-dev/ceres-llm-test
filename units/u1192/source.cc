// u1192 – ceres::internal::BlockSparseMatrix::UpdateCompressedRowSparseMatrixTranspose
// Trích từ internal/ceres/block_sparse_matrix.cc, dòng 474–482 (chỉ để xem, không compile)

void BlockSparseMatrix::UpdateCompressedRowSparseMatrixTranspose(
    CompressedRowSparseMatrix* crs_matrix) const {
  CHECK(crs_matrix != nullptr);
  CHECK_EQ(crs_matrix->num_rows(), num_cols_);
  CHECK_EQ(crs_matrix->num_cols(), num_rows_);
  CHECK_EQ(crs_matrix->num_nonzeros(), num_nonzeros_);
  UpdateCompressedRowSparseMatrixImpl<true>(
      crs_matrix, values(), transpose_block_structure_.get());
}
