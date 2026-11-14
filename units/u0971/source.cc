// u0971 – ceres::internal::TripletSparseMatrix::CopyData
// Trích từ internal/ceres/triplet_sparse_matrix.cc, dòng 164–170 (chỉ để xem, không compile)

void TripletSparseMatrix::CopyData(const TripletSparseMatrix& orig) {
  for (int i = 0; i < num_nonzeros_; ++i) {
    rows_[i] = orig.rows_[i];
    cols_[i] = orig.cols_[i];
    values_[i] = orig.values_[i];
  }
}
