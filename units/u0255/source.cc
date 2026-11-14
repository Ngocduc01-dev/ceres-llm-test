// u0255 – ceres::internal::CompressedRowSparseMatrix::num_nonzeros
// Trích từ internal/ceres/compressed_row_sparse_matrix.h, dòng 118–118 (chỉ để xem, không compile)

  int num_nonzeros() const final { return rows_[num_rows_]; }
