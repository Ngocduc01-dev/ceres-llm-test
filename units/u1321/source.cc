// u1321 – ceres::internal::CompressedRowSparseMatrix::FromTripletSparseMatrixTransposed
// Trích từ internal/ceres/compressed_row_sparse_matrix.cc, dòng 187–191 (chỉ để xem, không compile)

std::unique_ptr<CompressedRowSparseMatrix>
CompressedRowSparseMatrix::FromTripletSparseMatrixTransposed(
    const TripletSparseMatrix& input) {
  return CompressedRowSparseMatrix::FromTripletSparseMatrix(input, true);
}
