// u0902 – ceres::internal::TripletSparseMatrix::SetZero
// Trích từ internal/ceres/triplet_sparse_matrix.cc, dòng 147–150 (chỉ để xem, không compile)

void TripletSparseMatrix::SetZero() {
  std::fill(values_.get(), values_.get() + max_num_nonzeros_, 0.0);
  num_nonzeros_ = 0;
}
