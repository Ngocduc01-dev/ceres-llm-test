// u1224 – ceres::internal::(anonymous)::SetBlockStructureOfCompressedRowSparseMatrix
// Trích từ internal/ceres/block_sparse_matrix.cc, dòng 161–173 (chỉ để xem, không compile)

void SetBlockStructureOfCompressedRowSparseMatrix(
    CompressedRowSparseMatrix* crs_matrix,
    CompressedRowBlockStructure* block_structure) {
  const int num_row_blocks = block_structure->rows.size();
  auto& row_blocks = *crs_matrix->mutable_row_blocks();
  row_blocks.resize(num_row_blocks);
  for (int i = 0; i < num_row_blocks; ++i) {
    row_blocks[i] = block_structure->rows[i].block;
  }

  auto& col_blocks = *crs_matrix->mutable_col_blocks();
  col_blocks = block_structure->cols;
}
