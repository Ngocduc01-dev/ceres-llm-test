// u0594 – ceres::internal::(anonymous)::RowColLessThan::operator()
// Trích từ internal/ceres/compressed_row_sparse_matrix.cc, dòng 61–66 (chỉ để xem, không compile)

  bool operator()(const int x, const int y) const {
    if (rows[x] == rows[y]) {
      return (cols[x] < cols[y]);
    }
    return (rows[x] < rows[y]);
  }
