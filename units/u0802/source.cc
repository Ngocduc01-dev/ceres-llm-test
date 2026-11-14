// u0802 – ceres::internal::(anonymous)::ComputeCumulativeNumberOfNonZeros
// Trích từ internal/ceres/block_sparse_matrix.cc, dòng 56–65 (chỉ để xem, không compile)

void ComputeCumulativeNumberOfNonZeros(std::vector<CompressedList>& rows) {
  if (rows.empty()) {
    return;
  }
  rows[0].cumulative_nnz = rows[0].nnz;
  for (int c = 1; c < rows.size(); ++c) {
    const int curr_nnz = rows[c].nnz;
    rows[c].cumulative_nnz = curr_nnz + rows[c - 1].cumulative_nnz;
  }
}
