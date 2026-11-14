// u1348 – ceres::internal::BlockRandomAccessDiagonalMatrix::BlockRandomAccessDiagonalMatrix
// Trích từ internal/ceres/block_random_access_diagonal_matrix.cc, dòng 50–60 (chỉ để xem, không compile)

BlockRandomAccessDiagonalMatrix::BlockRandomAccessDiagonalMatrix(
    const std::vector<Block>& blocks, ContextImpl* context, int num_threads)
    : context_(context), num_threads_(num_threads) {
  m_ = CompressedRowSparseMatrix::CreateBlockDiagonalMatrix(nullptr, blocks);
  double* values = m_->mutable_values();
  layout_.reserve(blocks.size());
  for (auto& block : blocks) {
    layout_.emplace_back(std::make_unique<CellInfo>(values));
    values += block.size * block.size;
  }
}
