// u1319 – ceres::internal::BlockSparseMatrix::ToCompressedRowSparseMatrix
// Trích từ internal/ceres/block_sparse_matrix.cc, dòng 462–472 (chỉ để xem, không compile)

std::unique_ptr<CompressedRowSparseMatrix>
BlockSparseMatrix::ToCompressedRowSparseMatrix() const {
  auto crs_matrix = CreateStructureOfCompressedRowSparseMatrix<false>(
      values(), num_rows_, num_cols_, num_nonzeros_, block_structure_.get());

  SetBlockStructureOfCompressedRowSparseMatrix(crs_matrix.get(),
                                               block_structure_.get());

  UpdateCompressedRowSparseMatrix(crs_matrix.get());
  return crs_matrix;
}
