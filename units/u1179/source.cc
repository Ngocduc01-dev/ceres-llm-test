// u1179 – ceres::internal::TripletSparseMatrix::AppendCols
// Trích từ internal/ceres/triplet_sparse_matrix.cc, dòng 226–235 (chỉ để xem, không compile)

void TripletSparseMatrix::AppendCols(const TripletSparseMatrix& B) {
  CHECK_EQ(B.num_rows(), num_rows_);
  Reserve(num_nonzeros_ + B.num_nonzeros_);
  for (int i = 0; i < B.num_nonzeros_; ++i, ++num_nonzeros_) {
    rows_.get()[num_nonzeros_] = B.rows()[i];
    cols_.get()[num_nonzeros_] = B.cols()[i] + num_cols_;
    values_.get()[num_nonzeros_] = B.values()[i];
  }
  num_cols_ = num_cols_ + B.num_cols();
}
