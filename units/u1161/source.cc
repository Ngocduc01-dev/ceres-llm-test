// u1161 – ceres::internal::DenseSparseMatrix::DenseSparseMatrix
// Trích từ internal/ceres/dense_sparse_matrix.cc, dòng 46–56 (chỉ để xem, không compile)

DenseSparseMatrix::DenseSparseMatrix(const TripletSparseMatrix& m)
    : m_(Matrix::Zero(m.num_rows(), m.num_cols())) {
  const double* values = m.values();
  const int* rows = m.rows();
  const int* cols = m.cols();
  int num_nonzeros = m.num_nonzeros();

  for (int i = 0; i < num_nonzeros; ++i) {
    m_(rows[i], cols[i]) += values[i];
  }
}
