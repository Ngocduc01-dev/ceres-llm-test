// u0856 – ceres::internal::EigenSparseCholeskyTemplate::StorageType
// Trích từ internal/ceres/eigensparse.cc, dòng 56–58 (chỉ để xem, không compile)

  CompressedRowSparseMatrix::StorageType StorageType() const final {
    return CompressedRowSparseMatrix::StorageType::LOWER_TRIANGULAR;
  }
