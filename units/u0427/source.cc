// u0427 – ceres::internal::TripletSparseMatrix::mutable_values
// Trích từ internal/ceres/triplet_sparse_matrix.h, dòng 81–81 (chỉ để xem, không compile)

  double* mutable_values() final      { return values_.get(); }
