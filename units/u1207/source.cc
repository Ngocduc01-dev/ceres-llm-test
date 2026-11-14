// u1207 – ceres::internal::BlockSparseMatrix::DeleteRowBlocks
// Trích từ internal/ceres/block_sparse_matrix.cc, dòng 669–709 (chỉ để xem, không compile)

void BlockSparseMatrix::DeleteRowBlocks(const int delta_row_blocks) {
  const int num_row_blocks = block_structure_->rows.size();
  const int new_num_row_blocks = num_row_blocks - delta_row_blocks;
  int delta_num_nonzeros = 0;
  int delta_num_rows = 0;
  const std::vector<Block>& column_blocks = block_structure_->cols;
  for (int i = 0; i < delta_row_blocks; ++i) {
    const CompressedRow& row = block_structure_->rows[num_row_blocks - i - 1];
    delta_num_rows += row.block.size;
    for (int c = 0; c < row.cells.size(); ++c) {
      const Cell& cell = row.cells[c];
      delta_num_nonzeros += row.block.size * column_blocks[cell.block_id].size;

      if (transpose_block_structure_) {
        auto& col_cells = transpose_block_structure_->rows[cell.block_id].cells;
        while (!col_cells.empty() &&
               col_cells.back().block_id >= new_num_row_blocks) {
          const int del_block_id = col_cells.back().block_id;
          const int del_block_rows =
              block_structure_->rows[del_block_id].block.size;
          const int del_block_cols = column_blocks[cell.block_id].size;
          const int del_cell_nnz = del_block_rows * del_block_cols;
          transpose_block_structure_->rows[cell.block_id].nnz -= del_cell_nnz;
          col_cells.pop_back();
        }
      }
    }
  }
  num_nonzeros_ -= delta_num_nonzeros;
  num_rows_ -= delta_num_rows;
  block_structure_->rows.resize(new_num_row_blocks);

  if (transpose_block_structure_ == nullptr) {
    return;
  }
  for (int i = 0; i < delta_row_blocks; ++i) {
    transpose_block_structure_->cols.pop_back();
  }

  ComputeCumulativeNumberOfNonZeros(transpose_block_structure_->rows);
}
