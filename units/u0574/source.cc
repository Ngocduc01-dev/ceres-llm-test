// u0574 – ceres::internal::BlockRandomAccessSparseMatrix::IntPairToInt64
// Trích từ internal/ceres/block_random_access_sparse_matrix.h, dòng 99–101 (chỉ để xem, không compile)

  int64_t IntPairToInt64(int row, int col) const {
    return row * kRowShift + col;
  }
