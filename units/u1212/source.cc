// u1212 – ceres::internal::PartitionedMatrixView::PartitionedMatrixView<kRowBlockSize, kEBlockSize, kFBlockSize>
// Trích từ internal/ceres/partitioned_matrix_view_impl.h, dòng 47–105 (chỉ để xem, không compile)

template <int kRowBlockSize, int kEBlockSize, int kFBlockSize>
PartitionedMatrixView<kRowBlockSize, kEBlockSize, kFBlockSize>::
    PartitionedMatrixView(const LinearSolver::Options& options,
                          const BlockSparseMatrix& matrix)

    : options_(options), matrix_(matrix) {
  const CompressedRowBlockStructure* bs = matrix_.block_structure();
  CHECK(bs != nullptr);

  num_col_blocks_e_ = options_.elimination_groups[0];
  num_col_blocks_f_ = bs->cols.size() - num_col_blocks_e_;

  // Compute the number of row blocks in E. The number of row blocks
  // in E maybe less than the number of row blocks in the input matrix
  // as some of the row blocks at the bottom may not have any
  // e_blocks. For a definition of what an e_block is, please see
  // schur_complement_solver.h
  num_row_blocks_e_ = 0;
  for (const auto& row : bs->rows) {
    const std::vector<Cell>& cells = row.cells;
    if (cells[0].block_id < num_col_blocks_e_) {
      ++num_row_blocks_e_;
    }
  }

  // Compute the number of columns in E and F.
  num_cols_e_ = 0;
  num_cols_f_ = 0;

  for (int c = 0; c < bs->cols.size(); ++c) {
    const Block& block = bs->cols[c];
    if (c < num_col_blocks_e_) {
      num_cols_e_ += block.size;
    } else {
      num_cols_f_ += block.size;
    }
  }

  CHECK_EQ(num_cols_e_ + num_cols_f_, matrix_.num_cols());

  auto transpose_bs = matrix_.transpose_block_structure();
  const int num_threads = options_.num_threads;
  if (transpose_bs != nullptr && num_threads > 1) {
    int kMaxPartitions = num_threads * 4;
    e_cols_partition_ = PartitionRangeForParallelFor(
        0,
        num_col_blocks_e_,
        kMaxPartitions,
        transpose_bs->rows.data(),
        [](const CompressedRow& row) { return row.cumulative_nnz; });

    f_cols_partition_ = PartitionRangeForParallelFor(
        num_col_blocks_e_,
        num_col_blocks_e_ + num_col_blocks_f_,
        kMaxPartitions,
        transpose_bs->rows.data(),
        [](const CompressedRow& row) { return row.cumulative_nnz; });
  }
}
