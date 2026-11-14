// u1320 – ceres::internal::CompressedRowSparseMatrix::FromTripletSparseMatrix
// Trích từ internal/ceres/compressed_row_sparse_matrix.cc, dòng 181–185 (chỉ để xem, không compile)

std::unique_ptr<CompressedRowSparseMatrix>
CompressedRowSparseMatrix::FromTripletSparseMatrix(
    const TripletSparseMatrix& input) {
  return CompressedRowSparseMatrix::FromTripletSparseMatrix(input, false);
}
