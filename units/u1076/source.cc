// u1076 – ceres::internal::DenseSparseMatrix::ScaleColumns
// Trích từ internal/ceres/dense_sparse_matrix.cc, dòng 89–91 (chỉ để xem, không compile)

void DenseSparseMatrix::ScaleColumns(const double* scale) {
  m_ *= ConstVectorRef(scale, num_cols()).asDiagonal();
}
