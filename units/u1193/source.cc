// u1193 – ceres::internal::BlockSparseMatrix::UpdateCompressedRowSparseMatrix
// Trích từ internal/ceres/block_sparse_matrix.cc, dòng 483–491 (chỉ để xem, không compile)

void BlockSparseMatrix::UpdateCompressedRowSparseMatrix(
    CompressedRowSparseMatrix* crs_matrix) const {
  CHECK(crs_matrix != nullptr);
  CHECK_EQ(crs_matrix->num_rows(), num_rows_);
  CHECK_EQ(crs_matrix->num_cols(), num_cols_);
  CHECK_EQ(crs_matrix->num_nonzeros(), num_nonzeros_);
  UpdateCompressedRowSparseMatrixImpl<false>(
      crs_matrix, values(), block_structure_.get());
}
