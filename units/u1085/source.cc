// u1085 – ceres::internal::BlockRandomAccessDiagonalMatrix::GetCell
// Trích từ internal/ceres/block_random_access_diagonal_matrix.cc, dòng 62–81 (chỉ để xem, không compile)

CellInfo* BlockRandomAccessDiagonalMatrix::GetCell(int row_block_id,
                                                   int col_block_id,
                                                   int* row,
                                                   int* col,
                                                   int* row_stride,
                                                   int* col_stride) {
  if (row_block_id != col_block_id) {
    return nullptr;
  }

  auto& blocks = m_->row_blocks();
  const int stride = blocks[row_block_id].size;

  // Each cell is stored contiguously as its own little dense matrix.
  *row = 0;
  *col = 0;
  *row_stride = stride;
  *col_stride = stride;
  return layout_[row_block_id].get();
}
