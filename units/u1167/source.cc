// u1167 – ceres::internal::TripletSparseMatrix::operator=
// Trích từ internal/ceres/triplet_sparse_matrix.cc, dòng 95–107 (chỉ để xem, không compile)

TripletSparseMatrix& TripletSparseMatrix::operator=(
    const TripletSparseMatrix& rhs) {
  if (this == &rhs) {
    return *this;
  }
  num_rows_ = rhs.num_rows_;
  num_cols_ = rhs.num_cols_;
  num_nonzeros_ = rhs.num_nonzeros_;
  max_num_nonzeros_ = rhs.max_num_nonzeros_;
  AllocateMemory();
  CopyData(rhs);
  return *this;
}
