// u0660 – ceres::internal::DenseSparseMatrix::DenseSparseMatrix
// Trích từ internal/ceres/dense_sparse_matrix.cc, dòng 43–44 (chỉ để xem, không compile)

DenseSparseMatrix::DenseSparseMatrix(int num_rows, int num_cols)
    : m_(Matrix(num_rows, num_cols)) {}
