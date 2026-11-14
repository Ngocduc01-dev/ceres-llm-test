// u1105 – ceres::internal::BlockOrderingToScalarOrdering
// Trích từ internal/ceres/compressed_col_sparse_matrix_utils.cc, dòng 91–106 (chỉ để xem, không compile)

void BlockOrderingToScalarOrdering(const std::vector<Block>& blocks,
                                   const std::vector<int>& block_ordering,
                                   std::vector<int>* scalar_ordering) {
  CHECK_EQ(blocks.size(), block_ordering.size());
  const int num_blocks = blocks.size();
  scalar_ordering->resize(NumScalarEntries(blocks));
  int cursor = 0;
  for (int i = 0; i < num_blocks; ++i) {
    const int block_id = block_ordering[i];
    const int block_size = blocks[block_id].size;
    int block_position = blocks[block_id].position;
    for (int j = 0; j < block_size; ++j) {
      (*scalar_ordering)[cursor++] = block_position++;
    }
  }
}
