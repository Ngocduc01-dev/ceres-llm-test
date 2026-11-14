// u1277 – ceres::internal::VisibilityBasedPreconditioner::ScaleOffDiagonalCells
// Trích từ internal/ceres/visibility_based_preconditioner.cc, dòng 368–390 (chỉ để xem, không compile)

void VisibilityBasedPreconditioner::ScaleOffDiagonalCells() {
  for (const auto& block_pair : block_pairs_) {
    const int block1 = block_pair.first;
    const int block2 = block_pair.second;
    if (!IsBlockPairOffDiagonal(block1, block2)) {
      continue;
    }

    int r, c, row_stride, col_stride;
    CellInfo* cell_info =
        m_->GetCell(block1, block2, &r, &c, &row_stride, &col_stride);
    CHECK(cell_info != nullptr)
        << "Cell missing for block pair (" << block1 << "," << block2 << ")"
        << " cluster pair (" << cluster_membership_[block1] << " "
        << cluster_membership_[block2] << ")";

    // Ah the magic of tri-diagonal matrices and diagonal
    // dominance. See Lemma 1 in "Visibility Based Preconditioning
    // For Bundle Adjustment".
    MatrixRef m(cell_info->values, row_stride, col_stride);
    m.block(r, c, blocks_[block1].size, blocks_[block2].size) *= 0.5;
  }
}
