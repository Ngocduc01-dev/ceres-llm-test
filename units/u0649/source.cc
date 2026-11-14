// u0649 – ceres::internal::BlockRandomAccessDenseMatrix::GetCell
// Trích từ internal/ceres/block_random_access_dense_matrix.cc, dòng 56–67 (chỉ để xem, không compile)

CellInfo* BlockRandomAccessDenseMatrix::GetCell(const int row_block_id,
                                                const int col_block_id,
                                                int* row,
                                                int* col,
                                                int* row_stride,
                                                int* col_stride) {
  *row = blocks_[row_block_id].position;
  *col = blocks_[col_block_id].position;
  *row_stride = num_rows_;
  *col_stride = num_rows_;
  return &cell_infos_[row_block_id * blocks_.size() + col_block_id];
}
