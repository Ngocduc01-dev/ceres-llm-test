// u1072 – ceres::internal::BlockRandomAccessDiagonalMatrix::Invert
// Trích từ internal/ceres/block_random_access_diagonal_matrix.cc, dòng 90–100 (chỉ để xem, không compile)

void BlockRandomAccessDiagonalMatrix::Invert() {
  auto& blocks = m_->row_blocks();
  const int num_blocks = blocks.size();
  ParallelFor(context_, 0, num_blocks, num_threads_, [this, blocks](int i) {
    auto* cell_info = layout_[i].get();
    auto& block = blocks[i];
    MatrixRef b(cell_info->values, block.size, block.size);
    b = b.selfadjointView<Eigen::Upper>().llt().solve(
        Matrix::Identity(block.size, block.size));
  });
}
