// u0663 – ceres::internal::DenseSparseMatrix::ToDenseMatrix
// Trích từ internal/ceres/dense_sparse_matrix.cc, dòng 93–95 (chỉ để xem, không compile)

void DenseSparseMatrix::ToDenseMatrix(Matrix* dense_matrix) const {
  *dense_matrix = m_;
}
