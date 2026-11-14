// u1119 – ceres::internal::DynamicCompressedRowSparseMatrix::Finalize
// Trích từ internal/ceres/dynamic_compressed_row_sparse_matrix.cc, dòng 65–99 (chỉ để xem, không compile)

void DynamicCompressedRowSparseMatrix::Finalize(int num_additional_elements) {
  // `num_additional_elements` is provided as an argument so that additional
  // storage can be reserved when it is known by the finalizer.
  CHECK_GE(num_additional_elements, 0);

  // Count the number of non-zeros and resize `cols_` and `values_`.
  int num_jacobian_nonzeros = 0;
  for (const auto& dynamic_col : dynamic_cols_) {
    num_jacobian_nonzeros += dynamic_col.size();
  }

  SetMaxNumNonZeros(num_jacobian_nonzeros + num_additional_elements);

  // Flatten `dynamic_cols_` into `cols_` and `dynamic_values_`
  // into `values_`.
  int index_into_values_and_cols = 0;
  for (int i = 0; i < num_rows(); ++i) {
    mutable_rows()[i] = index_into_values_and_cols;
    const int num_nonzero_columns = dynamic_cols_[i].size();
    if (num_nonzero_columns > 0) {
      memcpy(mutable_cols() + index_into_values_and_cols,
             &dynamic_cols_[i][0],
             dynamic_cols_[i].size() * sizeof(dynamic_cols_[0][0]));
      memcpy(mutable_values() + index_into_values_and_cols,
             &dynamic_values_[i][0],
             dynamic_values_[i].size() * sizeof(dynamic_values_[0][0]));
      index_into_values_and_cols += dynamic_cols_[i].size();
    }
  }
  mutable_rows()[num_rows()] = index_into_values_and_cols;

  CHECK_EQ(index_into_values_and_cols, num_jacobian_nonzeros)
      << "Ceres bug: final index into values_ and cols_ should be equal to "
      << "the number of jacobian nonzeros. Please contact the developers!";
}
