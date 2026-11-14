// u0605 – ceres::internal::(anonymous)::AddRandomBlock
// Trích từ internal/ceres/compressed_row_sparse_matrix.cc, dòng 121–137 (chỉ để xem, không compile)

template <class RandomNormalFunctor>
void AddRandomBlock(const int num_rows,
                    const int num_cols,
                    const int row_block_begin,
                    const int col_block_begin,
                    RandomNormalFunctor&& randn,
                    std::vector<int>* rows,
                    std::vector<int>* cols,
                    std::vector<double>* values) {
  for (int r = 0; r < num_rows; ++r) {
    for (int c = 0; c < num_cols; ++c) {
      rows->push_back(row_block_begin + r);
      cols->push_back(col_block_begin + c);
      values->push_back(randn());
    }
  }
}
