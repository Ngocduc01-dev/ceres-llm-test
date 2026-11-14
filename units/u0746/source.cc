// u0746 – ceres::internal::DenseSparseMatrix::ToTextFile
// Trích từ internal/ceres/dense_sparse_matrix.cc, dòng 107–114 (chỉ để xem, không compile)

void DenseSparseMatrix::ToTextFile(FILE* file) const {
  CHECK(file != nullptr);
  for (int r = 0; r < m_.rows(); ++r) {
    for (int c = 0; c < m_.cols(); ++c) {
      fprintf(file, "% 10d % 10d %17f\n", r, c, m_(r, c));
    }
  }
}
