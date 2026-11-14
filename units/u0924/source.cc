// u0924 – ceres::internal::TripletSparseMatrix::set_num_nonzeros
// Trích từ internal/ceres/triplet_sparse_matrix.cc, dòng 152–156 (chỉ để xem, không compile)

void TripletSparseMatrix::set_num_nonzeros(int num_nonzeros) {
  CHECK_GE(num_nonzeros, 0);
  CHECK_LE(num_nonzeros, max_num_nonzeros_);
  num_nonzeros_ = num_nonzeros;
}
