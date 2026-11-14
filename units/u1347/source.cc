// u1347 – ceres::internal::BlockRandomAccessDenseMatrix::BlockRandomAccessDenseMatrix
// Trích từ internal/ceres/block_random_access_dense_matrix.cc, dòng 42–54 (chỉ để xem, không compile)

BlockRandomAccessDenseMatrix::BlockRandomAccessDenseMatrix(
    std::vector<Block> blocks, ContextImpl* context, int num_threads)
    : blocks_(std::move(blocks)), context_(context), num_threads_(num_threads) {
  const int num_blocks = blocks_.size();
  num_rows_ = NumScalarEntries(blocks_);
  values_ = std::make_unique<double[]>(num_rows_ * num_rows_);
  cell_infos_ = std::make_unique<CellInfo[]>(num_blocks * num_blocks);
  for (int i = 0; i < num_blocks * num_blocks; ++i) {
    cell_infos_[i].values = values_.get();
  }

  SetZero();
}
