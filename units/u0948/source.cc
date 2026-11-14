// u0948 – ceres::internal::TripletSparseMatrix::CreateFromTextFile
// Trích từ internal/ceres/triplet_sparse_matrix.cc, dòng 287–310 (chỉ để xem, không compile)

std::unique_ptr<TripletSparseMatrix> TripletSparseMatrix::CreateFromTextFile(
    FILE* file) {
  CHECK(file != nullptr);
  int num_rows = 0;
  int num_cols = 0;
  std::vector<int> rows;
  std::vector<int> cols;
  std::vector<double> values;
  while (true) {
    int row, col;
    double value;
    if (fscanf(file, "%d %d %lf", &row, &col, &value) != 3) {
      break;
    }
    rows.push_back(row);
    cols.push_back(col);
    values.push_back(value);
    num_rows = std::max(num_rows, row + 1);
    num_cols = std::max(num_cols, col + 1);
  }
  VLOG(1) << "Read " << rows.size() << " nonzeros from file.";
  return std::make_unique<TripletSparseMatrix>(
      num_rows, num_cols, rows, cols, values);
}
