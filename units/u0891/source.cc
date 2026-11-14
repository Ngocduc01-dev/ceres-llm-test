// u0891 – ceres::internal::RefinedSparseCholesky::StorageType
// Trích từ internal/ceres/sparse_cholesky.cc, dòng 128–131 (chỉ để xem, không compile)

CompressedRowSparseMatrix::StorageType RefinedSparseCholesky::StorageType()
    const {
  return sparse_cholesky_->StorageType();
}
