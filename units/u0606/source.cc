// u0606 – ceres::internal::(anonymous)::AddSymmetricRandomBlock
// Trích từ internal/ceres/compressed_row_sparse_matrix.cc, dòng 139–159 (chỉ để xem, không compile)

template <class RandomNormalFunctor>
void AddSymmetricRandomBlock(const int num_rows,
                             const int row_block_begin,
                             RandomNormalFunctor&& randn,
                             std::vector<int>* rows,
                             std::vector<int>* cols,
                             std::vector<double>* values) {
  for (int r = 0; r < num_rows; ++r) {
    for (int c = r; c < num_rows; ++c) {
      const double v = randn();
      rows->push_back(row_block_begin + r);
      cols->push_back(row_block_begin + c);
      values->push_back(v);
      if (r != c) {
        rows->push_back(row_block_begin + c);
        cols->push_back(row_block_begin + r);
        values->push_back(v);
      }
    }
  }
}
