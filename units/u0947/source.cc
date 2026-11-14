// u0947 – ceres::internal::TripletSparseMatrix::AllTripletsWithinBounds
// Trích từ internal/ceres/triplet_sparse_matrix.cc, dòng 109–119 (chỉ để xem, không compile)

bool TripletSparseMatrix::AllTripletsWithinBounds() const {
  for (int i = 0; i < num_nonzeros_; ++i) {
    // clang-format off
    if ((rows_[i] < 0) || (rows_[i] >= num_rows_) ||
        (cols_[i] < 0) || (cols_[i] >= num_cols_)) {
      return false;
    }
    // clang-format on
  }
  return true;
}
