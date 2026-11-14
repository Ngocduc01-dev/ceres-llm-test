// u1178 – ceres::internal::TripletSparseMatrix::AppendRows
// Trích từ internal/ceres/triplet_sparse_matrix.cc, dòng 215–224 (chỉ để xem, không compile)

void TripletSparseMatrix::AppendRows(const TripletSparseMatrix& B) {
  CHECK_EQ(B.num_cols(), num_cols_);
  Reserve(num_nonzeros_ + B.num_nonzeros_);
  for (int i = 0; i < B.num_nonzeros_; ++i) {
    rows_.get()[num_nonzeros_] = B.rows()[i] + num_rows_;
    cols_.get()[num_nonzeros_] = B.cols()[i];
    values_.get()[num_nonzeros_++] = B.values()[i];
  }
  num_rows_ = num_rows_ + B.num_rows();
}
