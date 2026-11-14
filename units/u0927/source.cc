// u0927 – ceres::internal::TripletSparseMatrix::ToTextFile
// Trích từ internal/ceres/triplet_sparse_matrix.cc, dòng 280–285 (chỉ để xem, không compile)

void TripletSparseMatrix::ToTextFile(FILE* file) const {
  CHECK(file != nullptr);
  for (int i = 0; i < num_nonzeros_; ++i) {
    fprintf(file, "% 10d % 10d %17f\n", rows_[i], cols_[i], values_[i]);
  }
}
