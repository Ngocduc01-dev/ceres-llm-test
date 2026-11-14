// u1188 – ceres::internal::TripletSparseMatrix::TripletSparseMatrix
// Trích từ internal/ceres/triplet_sparse_matrix.cc, dòng 51–63 (chỉ để xem, không compile)

TripletSparseMatrix::TripletSparseMatrix(int num_rows,
                                         int num_cols,
                                         int max_num_nonzeros)
    : num_rows_(num_rows),
      num_cols_(num_cols),
      max_num_nonzeros_(max_num_nonzeros),
      num_nonzeros_(0) {
  // All the sizes should at least be zero
  CHECK_GE(num_rows, 0);
  CHECK_GE(num_cols, 0);
  CHECK_GE(max_num_nonzeros, 0);
  AllocateMemory();
}
