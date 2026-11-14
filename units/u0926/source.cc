// u0926 – ceres::internal::TripletSparseMatrix::ScaleColumns
// Trích từ internal/ceres/triplet_sparse_matrix.cc, dòng 194–199 (chỉ để xem, không compile)

void TripletSparseMatrix::ScaleColumns(const double* scale) {
  CHECK(scale != nullptr);
  for (int i = 0; i < num_nonzeros_; ++i) {
    values_[i] = values_[i] * scale[cols_[i]];
  }
}
