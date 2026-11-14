// u0940 – ceres::internal::TripletSparseMatrix::Reserve
// Trích từ internal/ceres/triplet_sparse_matrix.cc, dòng 121–145 (chỉ để xem, không compile)

void TripletSparseMatrix::Reserve(int new_max_num_nonzeros) {
  CHECK_LE(num_nonzeros_, new_max_num_nonzeros)
      << "Reallocation will cause data loss";

  // Nothing to do if we have enough space already.
  if (new_max_num_nonzeros <= max_num_nonzeros_) return;

  std::unique_ptr<int[]> new_rows =
      std::make_unique<int[]>(new_max_num_nonzeros);
  std::unique_ptr<int[]> new_cols =
      std::make_unique<int[]>(new_max_num_nonzeros);
  std::unique_ptr<double[]> new_values =
      std::make_unique<double[]>(new_max_num_nonzeros);

  for (int i = 0; i < num_nonzeros_; ++i) {
    new_rows[i] = rows_[i];
    new_cols[i] = cols_[i];
    new_values[i] = values_[i];
  }

  rows_ = std::move(new_rows);
  cols_ = std::move(new_cols);
  values_ = std::move(new_values);
  max_num_nonzeros_ = new_max_num_nonzeros;
}
