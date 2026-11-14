// u1235 – ceres::internal::(anonymous)::CreateStructureOfCompressedRowSparseMatrix
// Trích từ internal/ceres/block_sparse_matrix.cc, dòng 67–118 (chỉ để xem, không compile)

template <bool transpose>
std::unique_ptr<CompressedRowSparseMatrix>
CreateStructureOfCompressedRowSparseMatrix(
    const double* values,
    int num_rows,
    int num_cols,
    int num_nonzeros,
    const CompressedRowBlockStructure* block_structure) {
  auto crs_matrix = std::make_unique<CompressedRowSparseMatrix>(
      num_rows, num_cols, num_nonzeros);
  auto crs_cols = crs_matrix->mutable_cols();
  auto crs_rows = crs_matrix->mutable_rows();
  int value_offset = 0;
  const int num_row_blocks = block_structure->rows.size();
  const auto& cols = block_structure->cols;
  *crs_rows++ = 0;
  for (int row_block_id = 0; row_block_id < num_row_blocks; ++row_block_id) {
    const auto& row_block = block_structure->rows[row_block_id];
    // Empty row block: only requires setting row offsets
    if (row_block.cells.empty()) {
      std::fill(crs_rows, crs_rows + row_block.block.size, value_offset);
      crs_rows += row_block.block.size;
      continue;
    }

    int row_nnz = 0;
    if constexpr (transpose) {
      // Transposed block structure comes with nnz in row-block filled-in
      row_nnz = row_block.nnz / row_block.block.size;
    } else {
      // Nnz field of non-transposed block structure is not filled and it can
      // have non-sequential structure (consider the case of jacobian for
      // Schur-complement solver: E and F blocks are stored separately).
      for (auto& c : row_block.cells) {
        row_nnz += cols[c.block_id].size;
      }
    }

    // Row-wise setup of matrix structure
    for (int row = 0; row < row_block.block.size; ++row) {
      value_offset += row_nnz;
      *crs_rows++ = value_offset;
      for (auto& c : row_block.cells) {
        const int col_block_size = cols[c.block_id].size;
        const int col_position = cols[c.block_id].position;
        std::iota(crs_cols, crs_cols + col_block_size, col_position);
        crs_cols += col_block_size;
      }
    }
  }
  return crs_matrix;
}
