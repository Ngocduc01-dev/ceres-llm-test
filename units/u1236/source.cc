// u1236 – ceres::internal::CompressedRowSparseMatrix::FromTripletSparseMatrix
// Trích từ internal/ceres/compressed_row_sparse_matrix.cc, dòng 193–252 (chỉ để xem, không compile)

std::unique_ptr<CompressedRowSparseMatrix>
CompressedRowSparseMatrix::FromTripletSparseMatrix(
    const TripletSparseMatrix& input, bool transpose) {
  int num_rows = input.num_rows();
  int num_cols = input.num_cols();
  const int* rows = input.rows();
  const int* cols = input.cols();
  const double* values = input.values();

  if (transpose) {
    std::swap(num_rows, num_cols);
    std::swap(rows, cols);
  }

  // index is the list of indices into the TripletSparseMatrix input.
  std::vector<int> index(input.num_nonzeros(), 0);
  for (int i = 0; i < input.num_nonzeros(); ++i) {
    index[i] = i;
  }

  // Sort index such that the entries of m are ordered by row and ties
  // are broken by column.
  std::sort(index.begin(), index.end(), RowColLessThan(rows, cols));

  VLOG(1) << "# of rows: " << num_rows << " # of columns: " << num_cols
          << " num_nonzeros: " << input.num_nonzeros() << ". Allocating "
          << ((num_rows + 1) * sizeof(int) +           // NOLINT
              input.num_nonzeros() * sizeof(int) +     // NOLINT
              input.num_nonzeros() * sizeof(double));  // NOLINT

  auto output = std::make_unique<CompressedRowSparseMatrix>(
      num_rows, num_cols, input.num_nonzeros());

  if (num_rows == 0) {
    // No data to copy.
    return output;
  }

  // Copy the contents of the cols and values array in the order given
  // by index and count the number of entries in each row.
  int* output_rows = output->mutable_rows();
  int* output_cols = output->mutable_cols();
  double* output_values = output->mutable_values();

  output_rows[0] = 0;
  for (int i = 0; i < index.size(); ++i) {
    const int idx = index[i];
    ++output_rows[rows[idx] + 1];
    output_cols[i] = cols[idx];
    output_values[i] = values[idx];
  }

  // Find the cumulative sum of the row counts.
  for (int i = 1; i < num_rows + 1; ++i) {
    output_rows[i] += output_rows[i - 1];
  }

  CHECK_EQ(output->num_nonzeros(), input.num_nonzeros());
  return output;
}
