// u1444 – ceres::internal::BlockSparseMatrix::BlockSparseMatrix
// Trích từ internal/ceres/block_sparse_matrix.cc, dòng 177–215 (chỉ để xem, không compile)

BlockSparseMatrix::BlockSparseMatrix(
    CompressedRowBlockStructure* block_structure, bool use_page_locked_memory)
    : use_page_locked_memory_(use_page_locked_memory),
      num_rows_(0),
      num_cols_(0),
      num_nonzeros_(0),
      block_structure_(block_structure) {
  CHECK(block_structure_ != nullptr);

  // Count the number of columns in the matrix.
  for (auto& col : block_structure_->cols) {
    num_cols_ += col.size;
  }

  // Count the number of non-zero entries and the number of rows in
  // the matrix.
  for (int i = 0; i < block_structure_->rows.size(); ++i) {
    int row_block_size = block_structure_->rows[i].block.size;
    num_rows_ += row_block_size;

    const std::vector<Cell>& cells = block_structure_->rows[i].cells;
    for (const auto& cell : cells) {
      int col_block_id = cell.block_id;
      int col_block_size = block_structure_->cols[col_block_id].size;
      num_nonzeros_ += col_block_size * row_block_size;
    }
  }

  CHECK_GE(num_rows_, 0);
  CHECK_GE(num_cols_, 0);
  CHECK_GE(num_nonzeros_, 0);
  VLOG(2) << "Allocating values array with " << num_nonzeros_ * sizeof(double)
          << " bytes.";  // NOLINT

  values_ = AllocateValues(num_nonzeros_);
  max_num_nonzeros_ = num_nonzeros_;
  CHECK(values_ != nullptr);
  AddTransposeBlockStructure();
}
