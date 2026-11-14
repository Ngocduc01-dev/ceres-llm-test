// u1233 – ceres::internal::(anonymous)::UpdateCompressedRowSparseMatrixImpl
// Trích từ internal/ceres/block_sparse_matrix.cc, dòng 120–159 (chỉ để xem, không compile)

template <bool transpose>
void UpdateCompressedRowSparseMatrixImpl(
    CompressedRowSparseMatrix* crs_matrix,
    const double* values,
    const CompressedRowBlockStructure* block_structure) {
  auto crs_values = crs_matrix->mutable_values();
  auto crs_rows = crs_matrix->mutable_rows();
  const int num_row_blocks = block_structure->rows.size();
  const auto& cols = block_structure->cols;
  for (int row_block_id = 0; row_block_id < num_row_blocks; ++row_block_id) {
    const auto& row_block = block_structure->rows[row_block_id];
    const int row_block_size = row_block.block.size;
    const int row_nnz = crs_rows[1] - crs_rows[0];
    crs_rows += row_block_size;

    if (row_nnz == 0) {
      continue;
    }

    MatrixRef crs_row_block(crs_values, row_block_size, row_nnz);
    int col_offset = 0;
    for (auto& c : row_block.cells) {
      const int col_block_size = cols[c.block_id].size;
      auto crs_cell =
          crs_row_block.block(0, col_offset, row_block_size, col_block_size);
      if constexpr (transpose) {
        // Transposed matrix is filled using transposed block-strucutre
        ConstMatrixRef cell(
            values + c.position, col_block_size, row_block_size);
        crs_cell = cell.transpose();
      } else {
        ConstMatrixRef cell(
            values + c.position, row_block_size, col_block_size);
        crs_cell = cell;
      }
      col_offset += col_block_size;
    }
    crs_values += row_nnz * row_block_size;
  }
}
