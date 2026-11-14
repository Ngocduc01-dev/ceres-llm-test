// u0966 – ceres::internal::TripletSparseMatrix::AllocateMemory
// Trích từ internal/ceres/triplet_sparse_matrix.cc, dòng 158–162 (chỉ để xem, không compile)

void TripletSparseMatrix::AllocateMemory() {
  rows_ = std::make_unique<int[]>(max_num_nonzeros_);
  cols_ = std::make_unique<int[]>(max_num_nonzeros_);
  values_ = std::make_unique<double[]>(max_num_nonzeros_);
}
