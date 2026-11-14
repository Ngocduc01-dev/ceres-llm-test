// u0575 – ceres::internal::BlockRandomAccessSparseMatrix::Int64ToIntPair
// Trích từ internal/ceres/block_random_access_sparse_matrix.h, dòng 103–106 (chỉ để xem, không compile)

  void Int64ToIntPair(int64_t index, int* row, int* col) const {
    *row = index / kRowShift;
    *col = index % kRowShift;
  }
