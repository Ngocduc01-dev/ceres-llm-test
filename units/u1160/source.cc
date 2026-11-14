// u1160 – ceres::internal::TripletSparseMatrix::TripletSparseMatrix
// Trích từ internal/ceres/triplet_sparse_matrix.cc, dòng 85–93 (chỉ để xem, không compile)

TripletSparseMatrix::TripletSparseMatrix(const TripletSparseMatrix& orig)
    : SparseMatrix(),
      num_rows_(orig.num_rows_),
      num_cols_(orig.num_cols_),
      max_num_nonzeros_(orig.max_num_nonzeros_),
      num_nonzeros_(orig.num_nonzeros_) {
  AllocateMemory();
  CopyData(orig);
}
