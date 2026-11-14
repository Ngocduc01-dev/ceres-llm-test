// u0935 – ceres::internal::operator<<
// Trích từ internal/ceres/compressed_row_sparse_matrix.h, dòng 227–243 (chỉ để xem, không compile)

inline std::ostream& operator<<(std::ostream& s,
                                CompressedRowSparseMatrix::StorageType type) {
  switch (type) {
    case CompressedRowSparseMatrix::StorageType::UNSYMMETRIC:
      s << "UNSYMMETRIC";
      break;
    case CompressedRowSparseMatrix::StorageType::UPPER_TRIANGULAR:
      s << "UPPER_TRIANGULAR";
      break;
    case CompressedRowSparseMatrix::StorageType::LOWER_TRIANGULAR:
      s << "LOWER_TRIANGULAR";
      break;
    default:
      s << "UNKNOWN CompressedRowSparseMatrix::StorageType";
  }
  return s;
}
