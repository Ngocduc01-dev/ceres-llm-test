// u1219 – ceres::internal::InnerProductComputer::CreateResultMatrix
// Trích từ internal/ceres/inner_product_computer.cc, dòng 47–58 (chỉ để xem, không compile)

std::unique_ptr<CompressedRowSparseMatrix>
InnerProductComputer::CreateResultMatrix(
    const CompressedRowSparseMatrix::StorageType storage_type,
    const int num_nonzeros) {
  auto matrix = std::make_unique<CompressedRowSparseMatrix>(
      m_.num_cols(), m_.num_cols(), num_nonzeros);
  matrix->set_storage_type(storage_type);
  const CompressedRowBlockStructure* bs = m_.block_structure();
  *matrix->mutable_row_blocks() = bs->cols;
  *matrix->mutable_col_blocks() = bs->cols;
  return matrix;
}
