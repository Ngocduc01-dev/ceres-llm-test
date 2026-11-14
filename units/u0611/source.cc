// u0611 – ceres::internal::(anonymous)::TransposeForCompressedRowSparseStructure
// Trích từ internal/ceres/compressed_row_sparse_matrix.cc, dòng 72–119 (chỉ để xem, không compile)

void TransposeForCompressedRowSparseStructure(const int num_rows,
                                              const int num_cols,
                                              const int num_nonzeros,
                                              const int* rows,
                                              const int* cols,
                                              const double* values,
                                              int* transpose_rows,
                                              int* transpose_cols,
                                              double* transpose_values) {
  // Explicitly zero out transpose_rows.
  std::fill(transpose_rows, transpose_rows + num_cols + 1, 0);

  // Count the number of entries in each column of the original matrix
  // and assign to transpose_rows[col + 1].
  for (int idx = 0; idx < num_nonzeros; ++idx) {
    ++transpose_rows[cols[idx] + 1];
  }

  // Compute the starting position for each row in the transpose by
  // computing the cumulative sum of the entries of transpose_rows.
  for (int i = 1; i < num_cols + 1; ++i) {
    transpose_rows[i] += transpose_rows[i - 1];
  }

  // Populate transpose_cols and (optionally) transpose_values by
  // walking the entries of the source matrices. For each entry that
  // is added, the value of transpose_row is incremented allowing us
  // to keep track of where the next entry for that row should go.
  //
  // As a result transpose_row is shifted to the left by one entry.
  for (int r = 0; r < num_rows; ++r) {
    for (int idx = rows[r]; idx < rows[r + 1]; ++idx) {
      const int c = cols[idx];
      const int transpose_idx = transpose_rows[c]++;
      transpose_cols[transpose_idx] = r;
      if (values != nullptr && transpose_values != nullptr) {
        transpose_values[transpose_idx] = values[idx];
      }
    }
  }

  // This loop undoes the left shift to transpose_rows introduced by
  // the previous loop.
  for (int i = num_cols - 1; i > 0; --i) {
    transpose_rows[i] = transpose_rows[i - 1];
  }
  transpose_rows[0] = 0;
}
