// u0666 – ceres::internal::DenseSparseMatrix::num_nonzeros
// Trích từ internal/ceres/dense_sparse_matrix.cc, dòng 101–101 (chỉ để xem, không compile)

int DenseSparseMatrix::num_nonzeros() const { return m_.rows() * m_.cols(); }
