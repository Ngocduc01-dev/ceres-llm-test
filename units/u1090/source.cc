// u1090 – ceres::internal::BlockRandomAccessDiagonalMatrix::RightMultiplyAndAccumulate
// Trích từ internal/ceres/block_random_access_diagonal_matrix.cc, dòng 102–116 (chỉ để xem, không compile)

void BlockRandomAccessDiagonalMatrix::RightMultiplyAndAccumulate(
    const double* x, double* y) const {
  CHECK(x != nullptr);
  CHECK(y != nullptr);
  auto& blocks = m_->row_blocks();
  const int num_blocks = blocks.size();
  ParallelFor(
      context_, 0, num_blocks, num_threads_, [this, blocks, x, y](int i) {
        auto* cell_info = layout_[i].get();
        auto& block = blocks[i];
        ConstMatrixRef b(cell_info->values, block.size, block.size);
        VectorRef(y + block.position, block.size).noalias() +=
            b * ConstVectorRef(x + block.position, block.size);
      });
}
