// u1086 – ceres::internal::BlockRandomAccessSparseMatrix::GetCell
// Trích từ internal/ceres/block_random_access_sparse_matrix.cc, dòng 100–117 (chỉ để xem, không compile)

CellInfo* BlockRandomAccessSparseMatrix::GetCell(int row_block_id,
                                                 int col_block_id,
                                                 int* row,
                                                 int* col,
                                                 int* row_stride,
                                                 int* col_stride) {
  const auto it = layout_.find(IntPairToInt64(row_block_id, col_block_id));
  if (it == layout_.end()) {
    return nullptr;
  }

  // Each cell is stored contiguously as its own little dense matrix.
  *row = 0;
  *col = 0;
  *row_stride = blocks_[row_block_id].size;
  *col_stride = blocks_[col_block_id].size;
  return it->second.get();
}
