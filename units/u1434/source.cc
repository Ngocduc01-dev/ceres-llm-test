// u1434 – ceres::internal::TripletSparseMatrix::ToCRSMatrix
// Trích từ internal/ceres/triplet_sparse_matrix.cc, dòng 201–204 (chỉ để xem, không compile)

void TripletSparseMatrix::ToCRSMatrix(CRSMatrix* crs_matrix) const {
  CompressedRowSparseMatrix::FromTripletSparseMatrix(*this)->ToCRSMatrix(
      crs_matrix);
}
