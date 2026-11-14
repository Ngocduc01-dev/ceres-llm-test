// u1168 – ceres::internal::TripletSparseMatrix::CreateSparseDiagonalMatrix
// Trích từ internal/ceres/triplet_sparse_matrix.cc, dòng 266–278 (chỉ để xem, không compile)

std::unique_ptr<TripletSparseMatrix>
TripletSparseMatrix::CreateSparseDiagonalMatrix(const double* values,
                                                int num_rows) {
  std::unique_ptr<TripletSparseMatrix> m =
      std::make_unique<TripletSparseMatrix>(num_rows, num_rows, num_rows);
  for (int i = 0; i < num_rows; ++i) {
    m->mutable_rows()[i] = i;
    m->mutable_cols()[i] = i;
    m->mutable_values()[i] = values[i];
  }
  m->set_num_nonzeros(num_rows);
  return m;
}
