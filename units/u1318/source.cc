// u1318 – ceres::internal::BlockSparseMatrix::ToCompressedRowSparseMatrixTranspose
// Trích từ internal/ceres/block_sparse_matrix.cc, dòng 450–460 (chỉ để xem, không compile)

std::unique_ptr<CompressedRowSparseMatrix>
BlockSparseMatrix::ToCompressedRowSparseMatrixTranspose() const {
  auto bs = transpose_block_structure_.get();
  auto crs_matrix = CreateStructureOfCompressedRowSparseMatrix<true>(
      values(), num_cols_, num_rows_, num_nonzeros_, bs);

  SetBlockStructureOfCompressedRowSparseMatrix(crs_matrix.get(), bs);

  UpdateCompressedRowSparseMatrixTranspose(crs_matrix.get());
  return crs_matrix;
}
