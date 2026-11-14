// u0953 – ceres::internal::TripletSparseMatrix::CreateRandomMatrix
// Trích từ internal/ceres/triplet_sparse_matrix.cc, dòng 312–342 (chỉ để xem, không compile)

std::unique_ptr<TripletSparseMatrix> TripletSparseMatrix::CreateRandomMatrix(
    const TripletSparseMatrix::RandomMatrixOptions& options,
    std::mt19937& prng) {
  CHECK_GT(options.num_rows, 0);
  CHECK_GT(options.num_cols, 0);
  CHECK_GT(options.density, 0.0);
  CHECK_LE(options.density, 1.0);

  std::vector<int> rows;
  std::vector<int> cols;
  std::vector<double> values;
  std::uniform_real_distribution<double> uniform01(0.0, 1.0);
  std::normal_distribution<double> standard_normal;
  while (rows.empty()) {
    rows.clear();
    cols.clear();
    values.clear();
    for (int r = 0; r < options.num_rows; ++r) {
      for (int c = 0; c < options.num_cols; ++c) {
        if (uniform01(prng) <= options.density) {
          rows.push_back(r);
          cols.push_back(c);
          values.push_back(standard_normal(prng));
        }
      }
    }
  }

  return std::make_unique<TripletSparseMatrix>(
      options.num_rows, options.num_cols, rows, cols, values);
}
