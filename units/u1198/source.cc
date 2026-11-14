// u1198 – ceres::internal::TripletSparseMatrix::TripletSparseMatrix
// Trích từ internal/ceres/triplet_sparse_matrix.cc, dòng 65–83 (chỉ để xem, không compile)

TripletSparseMatrix::TripletSparseMatrix(const int num_rows,
                                         const int num_cols,
                                         const std::vector<int>& rows,
                                         const std::vector<int>& cols,
                                         const std::vector<double>& values)
    : num_rows_(num_rows),
      num_cols_(num_cols),
      max_num_nonzeros_(values.size()),
      num_nonzeros_(values.size()) {
  // All the sizes should at least be zero
  CHECK_GE(num_rows, 0);
  CHECK_GE(num_cols, 0);
  CHECK_EQ(rows.size(), cols.size());
  CHECK_EQ(rows.size(), values.size());
  AllocateMemory();
  std::copy(rows.begin(), rows.end(), rows_.get());
  std::copy(cols.begin(), cols.end(), cols_.get());
  std::copy(values.begin(), values.end(), values_.get());
}
